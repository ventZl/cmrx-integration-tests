Source tree for CMRX integration build(s)
=========================================

This is a source tree for CMRX integration builds. A simple project
for building CMRX on top of CubeMX-generated HAL is provided that
is used to build master branch of CMRX after each push to the branch.

The only purpose is to verify that the build builds for given CPU and
HAL platform without any issues.

rp2350-pico-sdk-riscv
----------------------

Build-only integration test for the RP2350 (Pico 2) RISC-V cores,
mirroring the rp2040-pico-sdk layout but targeting CMRX_ARCH=riscv.
Since the RISC-V port only needs to compile and link here, there is
no HIL execution: a green CI run only proves the firmware builds.

Building locally requires:

- PICO_SDK_PATH pointing at a Pico SDK checkout that includes RISC-V
  support (hardware_riscv_platform_timer, RP2350 RISC-V core
  definitions).
- PICO_PLATFORM=rp2350-riscv and PICO_BOARD=pico2.
- The riscv32-pico-elf toolchain from raspberrypi/pico-sdk-tools on
  PATH. This is the toolchain triple the Pico SDK's RISC-V preload
  file expects by default, so no PICO_GCC_TRIPLE override is needed.

With those in place:

    cmake -B build -S rp2350-pico-sdk-riscv \
      -DCMRX_UNIT_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug \
      -DPICO_PLATFORM=rp2350-riscv -DPICO_BOARD=pico2
    make -C build
