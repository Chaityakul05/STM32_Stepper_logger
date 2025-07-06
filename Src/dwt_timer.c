/*
 * dwt_timer.c
 *
 *  Created on: Jul 5, 2025
 *      Author: chait
 */

#include "dwt_timer.h"
#include "base.h"

void DWT_Delay_Init(void)
{
    // Enable TRC (Trace Control)
    DEMCR |= DEMCR_TRCENA;

    // Reset the cycle counter
    DWT_CYCCNT = 0;

    // Enable the cycle counter
    DWT_CTRL |= DWT_CTRL_CYCCNTENA;
}

void DWT_Delay_us(uint32_t us)
{
    uint32_t cycles = us * (SYS_FREQ / 1000000UL);
    uint32_t start = DWT_CYCCNT;

    while ((DWT_CYCCNT - start) < cycles);
}

uint32_t DWT_GetMicroseconds(void)
{
    return DWT_CYCCNT / (SYS_FREQ / 1000000);
}

