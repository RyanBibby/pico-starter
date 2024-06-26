cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME pico-boilerplate) # <-- Name your project/executable here!

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
include($ENV{PIMORONI_SDK_PATH}/pimoroni_pico_import.cmake)

# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Add your source files
add_executable(${NAME}
        main.cpp # <-- Add source files here!
)

# Include required libraries
# This assumes `pimoroni-pico` is stored alongside your project
include(common/pimoroni_i2c)
include(common/pimoroni_bus)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/hershey_fonts/hershey_fonts)
include(libraries/pico_display_2/pico_display_2)
include(drivers/rgbled/rgbled)
include(drivers/button/button)
include(drivers/st7789/st7789)
include(libraries/pico_graphics/pico_graphics)


# Don't forget to link the libraries you need!
target_link_libraries(${NAME}
    pimoroni_i2c
    pico_cyw43_arch_none
    pico_stdlib pico_multicore hardware_spi hardware_pwm hardware_dma pico_display_2 button rgbled st7789 pico_graphics # <-- List libraries here!
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# Set up files for the release packages
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
