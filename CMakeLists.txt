cmake_minimum_required(VERSION 3.12)

#Define project name
set(ProjectName IOTCooling)

# Set any variables required for importing libraries
SET(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName} ASM C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

#Setting c standard
set(CMAKE_C_STANDARD 11)

#Setting cpp standard
set(CMAKE_CXX_STANDARD 17)

#Set pico w board
set(PICO_BOARD pico_w)

set(PICO_MAX_SHARED_IRQ_HANDLERS 5)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add source code directory
add_subdirectory(src)


