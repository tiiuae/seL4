/*
 * Copyright 2021, Technology Innovation Institute
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <config.h>
#include <stdint.h>
#include <util.h>
#include <machine/io.h>
#include <plat/machine/devices_gen.h>

#ifdef CONFIG_PRINTING
void uart_drv_putchar(unsigned char c)
{
        volatile uint32_t *mb = ((uint32_t *) UART_PPTR);

        while (*mb & 0x80000000);

        *mb = ((uint32_t) c) |
                (0x81 << 24);

        while (*mb & 0x80000000);
}
#endif /* CONFIG_PRINTING */

#ifdef CONFIG_DEBUG_BUILD
unsigned char uart_drv_getchar(void)
{
    return 0;
}
#endif /* CONFIG_DEBUG_BUILD */
