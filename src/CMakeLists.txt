find_package(Perl)
if(NOT PERL_FOUND)
    message(FATAL_ERROR "Perl is needed for generating the fsdata.c file")
endif()



set(MAKE_FS_DATA_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/external/makefsdata)

if (NOT EXISTS ${MAKE_FS_DATA_SCRIPT})
        file(DOWNLOAD
                https://raw.githubusercontent.com/lwip-tcpip/lwip/e799c266facc3c70190676eccad49d6c2db2caac/src/apps/http/makefsdata/makefsdata
                ${MAKE_FS_DATA_SCRIPT}
                )
endif()

#Run perl script
message("Running makefsdata perl script")

execute_process(COMMAND
        perl ${MAKE_FS_DATA_SCRIPT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        ECHO_OUTPUT_VARIABLE
        ECHO_ERROR_VARIABLE
        )

message("Perl executing done")

file(RENAME fsdata.c my_fsdata.c)

add_executable(${ProjectName}
    one_wire.cpp
    ssi.cpp
    WebServer.cpp   
    task_ReadTemperature.cpp
    task_FanControl.cpp
    main.cpp
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName}
pico_cyw43_arch_lwip_threadsafe_background
pico_lwip_http
pico_stdlib 
FreeRTOS-Kernel-Heap4 
hardware_pwm
)



#Enable usb output, disable uart outputs
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${ProjectName})