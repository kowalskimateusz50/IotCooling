cmake_minimum_required(VERSION 3.12)

#Define project name
set(ProjectName IOTCooling)

# Define project 
project(${ProjectName} C CXX)

#Setting c standard
#set(CMAKE_C_STANDARD 17)

#Setting cpp standard
#set(CMAKE_CXX_STANDARD 20)

#Set pico w board
set(PICO_BOARD pico_w)

# Set any variables required for importing libraries
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add source code directory
add_subdirectory(src)

#Add pico-onewire library 
add_subdirectory(lib/pico-onewire)

