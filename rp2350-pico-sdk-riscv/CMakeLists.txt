cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
list(APPEND CMAKE_MODULE_PATH "${PICO_SDK_PATH}/external")

set(CMRX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmrx)
list(APPEND CMAKE_MODULE_PATH "${CMRX_PATH}/cmake")

include(pico_sdk_import)

project(rp2350_riscv_cmrx LANGUAGES C CXX ASM)

pico_sdk_init()

set(CMRX_ARCH riscv)
set(CMRX_HAL hal)
include(CMRX)

add_subdirectory(${CMRX_PATH} ${CMAKE_BINARY_DIR}/cmrx)

# The RP2350 RISC-V port relies on a handful of Pico SDK quirk files that
# are not yet part of the CMRX core sources (timer ISR wiring, exception
# dispatch and ecall handling). Building them as a separate OBJECT library
# keeps the CMRX core CMakeLists.txt untouched while still linking them
# straight into the firmware image.
add_library(cmrx_quirks OBJECT
    ${CMRX_PATH}/quirks/pico-sdk-riscv/cmrx_timer_isr.c
    ${CMRX_PATH}/quirks/pico-sdk-riscv/cmrx_exception_dispatcher.c
    ${CMRX_PATH}/quirks/pico-sdk-riscv/cmrx_ecall_handler.c
)
target_include_directories(cmrx_quirks PRIVATE ${CMRX_PATH}/include)
target_link_libraries(cmrx_quirks PRIVATE pico_base_headers hardware_regs)

add_subdirectory(src/hello_world)

add_firmware(rp2350_riscv_cmrx src/main.c src/timing_provider.c)
target_sources(rp2350_riscv_cmrx PRIVATE $<TARGET_OBJECTS:cmrx_quirks>)

# Link order is load-bearing: hello_world must be whole-archived so its
# OS_APPLICATION/OS_THREAD_CREATE registration symbols are pulled in even
# though nothing in cmrx/stdlib references them directly. Do not reorder.
target_link_libraries(rp2350_riscv_cmrx
    -Wl,--start-group
    -Wl,--whole-archive hello_world -Wl,--no-whole-archive
    cmrx
    stdlib
    -Wl,--end-group
    pico_stdlib
    hardware_exception
    hardware_riscv_platform_timer
)

pico_enable_stdio_uart(rp2350_riscv_cmrx 1)
pico_enable_stdio_usb(rp2350_riscv_cmrx 0)
