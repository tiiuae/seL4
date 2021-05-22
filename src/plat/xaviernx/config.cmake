#
# Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: GPL-2.0-only
#

cmake_minimum_required(VERSION 3.7.2)

declare_platform(xaviernx KernelPlatformXavierNX PLAT_XAVIERNX KernelSel4ArchAarch64)

if(KernelPlatformXavierNX)
    declare_seL4_arch(aarch64)


    set(KernelNVIDIACarmel ON)
    set(KernelArchArmV8a ON)
    set(KernelArmSMMU OFF)
    set(KernelAArch64SErrorIgnore ON)
    config_set(KernelARMPlatform ARM_PLAT xaviernx)
    config_set(KernelArmMach MACH "nvidia")
    list(APPEND KernelDTSList "tools/dts/xaviernx.dts")
    list(APPEND KernelDTSList "src/plat/xaviernx/overlay-xaviernx.dts")
    # TODO: check these
    declare_default_headers(
        TIMER_FREQUENCY 31250000
        MAX_IRQ 383
        INTERRUPT_CONTROLLER arch/machine/gic_v2.h
        NUM_PPI 32
        TIMER drivers/timer/arm_generic.h
        CLK_SHIFT 57u
        CLK_MAGIC 4611686019u
        KERNEL_WCET 10u SMMU drivers/smmu/smmuv2.h
        MAX_SID 128
        MAX_CB 64
    )
endif()

add_sources(
    DEP "KernelPlatformXavierNX"
    CFILES src/arch/arm/machine/gic_v2.c src/arch/arm/machine/l2c_nop.c
)
