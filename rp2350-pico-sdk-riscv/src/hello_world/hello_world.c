#include <cmrx/application.h>
#include <pico/stdlib.h>
#include <cmrx/ipc/timer.h>
#include <stdio.h>

/* Thread entrypoint for the hello_world application */
static int hello_world_thread(void * data)
{
    (void) data;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (1) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        printf("hello world\n");
        usleep(500000);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        usleep(500000);
    }
    return 0;
}

/* Grant the hello_world application access to the GPIO and SIO peripherals */
OS_APPLICATION_MMIO_RANGES(hello_world, 0x40000000, 0x50000000, 0xd0000000, 0xe0000000);

/* Declare the hello_world application */
OS_APPLICATION(hello_world);

/* Tell CMRX to automatically start a thread using `hello_world_thread` as an
 * entrypoint and having thread priority of 32 */
OS_THREAD_CREATE(hello_world, hello_world_thread, NULL, 32);
