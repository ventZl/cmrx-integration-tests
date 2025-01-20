set(blinky_SRCS blinky.c)
add_application(blinky ${blinky_SRCS})
target_link_libraries(blinky PRIVATE stdlib pico_stdlib_headers)

