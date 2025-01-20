cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${PICO_SDK_PATH}/external")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmrx/cmake")

include(pico_sdk_import)

project(blinky LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMSIS_ROOT ${PICO_SDK_PATH}/src/rp2_common/cmsis/stub/CMSIS)
set(DEVICE RP2040)
set(CMSIS_LINKER_FILE ${PICO_SDK_PATH}/src/rp2_common/pico_crt0/rp2040/memmap_default.ld)

include(FindCMSIS)

pico_sdk_init()

set(CMRX_ARCH arm)
set(CMRX_HAL cmsis)
include(CMRX)

add_subdirectory(cmrx)
add_subdirectory(src/blinky)

set(helloworld_SRCS src/main.c)
add_firmware(helloworld ${helloworld_SRCS})

target_link_libraries(helloworld cmrx aux_systick pico_stdlib cmsis_core)
target_add_applications(helloworld blinky)
