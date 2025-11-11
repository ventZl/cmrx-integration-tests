cmake_minimum_required(VERSION 3.22)

project(cmrx-on-linux)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmrx/cmake)

set(CMRX_ARCH linux)
set(CMRX_HAL posix)

include(CMRX)

add_subdirectory(cmrx)
add_subdirectory(src/init)

add_firmware(cmrx-on-linux src/main.c)
target_link_libraries(cmrx-on-linux cmrx)
target_add_applications(cmrx-on-linux init)

