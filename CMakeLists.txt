cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME rp2040-azure-rtos-blink)
set(CMAKE_BUILD_TYPE Debug)
set(PICO_BOARD pico_w)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(THREADX_ARCH "cortex_m0")
set(THREADX_TOOLCHAIN "gnu")

include(pico_sdk_import.cmake)

project(${PROJECT_NAME} C CXX ASM)

pico_sdk_init()

add_subdirectory(threadx)
add_executable(${PROJECT_NAME} 
    main.c
    threadx_main.c
    tx_initialize_low_level.S
)

pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    cmsis_core 
    azrtos::threadx
)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(${PROJECT_NAME} 
        pico_cyw43_arch_none
    )
endif()
