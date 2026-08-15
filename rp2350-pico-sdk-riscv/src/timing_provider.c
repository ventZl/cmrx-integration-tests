/*
 * Timing provider for RP2350 RISC-V using the machine timer.
 *
 * Uses the RISC-V mtime/mtimecmp registers via Pico SDK's
 * hardware/riscv_platform_timer.h. The tick generators are
 * initialised by Pico SDK's runtime_init_clocks() at
 * clk_ref / MHZ, producing a 1 MHz mtime rate (1 tick = 1 us).
 *
 * The machine timer interrupt (cause 7, vector entry
 * "j isr_riscv_machine_timer" in crt0_riscv.S) is handled by
 * the strong symbol in crt0_riscv_cmrx.S, which saves context,
 * calls cmrx_machine_timer_handler() below, then calls the
 * CMRX context-switch safe-point before restoring and mret.
 */

#include "timing_provider.h"
#include <cmrx/clock.h>
#include <hardware/riscv_platform_timer.h>
#include <hardware/regs/rvcsr.h>
#include <pico/time.h>
#include <stdint.h>
#include <stdbool.h>

static uint32_t timing_interval_us;

static void mtie_enable(void)
{
    uint32_t bit = RVCSR_MIE_MTIE_BITS;
    __asm__ volatile("csrs mie, %0" :: "r"(bit));
}

static void mtie_disable(void)
{
    uint32_t bit = RVCSR_MIE_MTIE_BITS;
    __asm__ volatile("csrc mie, %0" :: "r"(bit));
}

void cmrx_machine_timer_handler(void)
{
    riscv_timer_set_mtimecmp(riscv_timer_get_mtime() + timing_interval_us);
    os_sched_timing_callback((long)timing_interval_us);
}

void timing_provider_setup(int interval_ms)
{
    timing_interval_us = (uint32_t)interval_ms * 1000u;
}

void timing_provider_schedule(long delay_us)
{
    /* This provider only supports a fixed periodic tick (timing_interval_us),
     * so any non-zero delay_us just (re)arms the next tick; delay_us == 0
     * disables the timer interrupt instead of arming it. */
    if (delay_us == 0) {
        mtie_disable();
    } else {
        riscv_timer_set_mtimecmp(riscv_timer_get_mtime() + timing_interval_us);
        mtie_enable();
    }
}

void timing_provider_delay(long delay_us)
{
    busy_wait_us((uint64_t)delay_us);
}
