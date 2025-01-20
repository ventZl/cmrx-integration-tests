#include <cmrx/application.h>
#include <pico/stdlib.h>
#include <cmrx/ipc/timer.h>

static const unsigned blink_rate = 500000;

/* Main function for the blinky application */
static int blinky_main(void * data)
{
    (void) data;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (1) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        usleep(blink_rate);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        usleep(blink_rate);

    }
    return 0;

    return 0;
}

/* Grant the blinky application access to the GPIOA - GPIOE peripheral */
OS_APPLICATION_MMIO_RANGES(blinky, 0x40000000, 0x50000000, 0xd0000000, 0xe0000000);

/* Declare the blinky application */
OS_APPLICATION(blinky);

/* Tell CMRX to automatically start a thread using `blinky_main` as an
 * entrypoint and having thread priority of 32 */
OS_THREAD_CREATE(blinky, blinky_main, NULL, 32);

