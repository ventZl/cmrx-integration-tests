/*
 * Timing provider header for RP2350 RISC-V.
 *
 * This is application-local (not part of CMRX) since it uses
 * Pico SDK specific APIs for timer functionality.
 */
#pragma once

void timing_provider_setup(int interval_ms);
