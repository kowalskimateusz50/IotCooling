add_executable(${ProjectName}
    main.cpp
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(${ProjectName})

target_link_libraries(${ProjectName} 
    pico_stdlib 
    pico_cyw43_arch_none
    FreeRTOS-Kernel-Heap4 
    pico_one_wire
    )

#Enable usb output, disable uart outputs
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

