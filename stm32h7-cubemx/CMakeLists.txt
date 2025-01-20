cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmrx/cmake)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME tmp-cmrx-integration-build)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

set(CMSIS_ROOT ${CMAKE_SOURCE_DIR}/Drivers/CMSIS)
set(DEVICE stm32h753xx)
set(CMSIS_LINKER_FILE ${CMAKE_SOURCE_DIR}/stm32h753vihx_flash.ld)
set(SYSTEM_INCLUDE_FILENAME system_stm32h7xx.h)
include(FindCMSIS)

set(CMRX_ARCH arm)
set(CMRX_HAL cmsis)
include(CMRX)

add_subdirectory(cmrx)

# Create an executable object type
add_firmware(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

get_target_property(CUBEMX_INCLUDE_DIRECTORIES stm32cubemx INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(CUBEMX_COMPILE_DEFINITIONS stm32cubemx INTERFACE_COMPILE_DEFINITIONS)

add_library(stm32cubemx_headers INTERFACE)
target_include_directories(stm32cubemx_headers INTERFACE ${CUBEMX_INCLUDE_DIRECTORIES})
target_compile_definitions(stm32cubemx_headers INTERFACE ${CUBEMX_COMPILE_DEFINITIONS})

add_subdirectory(Core/Src/blinky)


# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    # Add user defined libraries
    cmrx
    aux_systick
)

target_add_applications(${CMAKE_PROJECT_NAME}
    blinky
)
