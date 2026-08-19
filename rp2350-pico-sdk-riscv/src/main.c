#include <cmrx/cmrx.h>
#include "timing_provider.h"

#include "pico/stdlib.h"
#include "hardware/clocks.h"

long timing_get_current_cpu_freq(void)
{
    return (long)clock_get_hz(clk_sys);
}

int main(void)
{
    stdio_init_all();

    timing_provider_setup(1);
    os_start();

    /* Should not reach here */
    return 0;
}
