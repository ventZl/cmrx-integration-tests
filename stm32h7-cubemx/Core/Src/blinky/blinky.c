#include <cmrx/application.h>
#include <stm32h7xx_hal.h>
#include <main.h>
#include <cmrx/ipc/timer.h>
#include <stdbool.h>

/* Main function for the blinky application */
static int blinky_main(void * data)
{
    (void) data;
    while (true) {
        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
        usleep(500000);
        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
        usleep(500000);
    }

    return 0;
}

/* Grant the blinky application access to the GPIOA - GPIOE peripheral */
OS_APPLICATION_MMIO_RANGES(blinky, 0x58020000, 0x58023000, 0x0, 0x0);

/* Declare the blinky application */
OS_APPLICATION(blinky);

/* Tell CMRX to automatically start a thread using `blinky_main` as an
 * entrypoint and having thread priority of 32 */
OS_THREAD_CREATE(blinky, blinky_main, NULL, 32);
