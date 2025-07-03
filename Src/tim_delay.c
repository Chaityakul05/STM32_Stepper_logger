/*
 * tim_delay.c
 *
 *  Created on: Jul 2, 2025
 *      Author: chait
 */


#include "tim_delay.h"
#include "base.h"

void TIM2_Delay_Init(void)
{
    // Enable clock for TIM2
    RCC_APB1ENR |= RCC_TIM2_EN;

    // Disable TIM2 during config
    TIM2_CR1 &= ~TIM_CR1_CEN;

    // Prescaler to get 1MHz → 1 tick = 1µs
    TIM2_PSC = TIM2_US_PRESCALER;

    // Optional: Max ARR value (not used in blocking delay)
    TIM2_ARR = 0xFFFF;

    TIM2_EGR |= (1 << 0);

    // Clear counter
    TIM2_CNT = 0;

    // Enable TIM2
    TIM2_CR1 |= TIM_CR1_CEN;
}

void TIM2_Delay_us(uint32_t us)
{
  TIM2_CR1 &= ~TIM_CR1_CEN;
  TIM2_CNT = 0;
  TIM2_CR1 |= TIM_CR1_CEN;
  while (TIM2_CNT < us);
}
