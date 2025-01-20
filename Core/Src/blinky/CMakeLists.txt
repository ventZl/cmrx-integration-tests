set(blinky_SRCS blinky.c)
add_application(blinky ${blinky_SRCS})
target_link_libraries(blinky PRIVATE stdlib stm32cubemx_headers)
