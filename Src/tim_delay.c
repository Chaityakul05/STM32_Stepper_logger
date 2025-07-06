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
    // Enable TIM2 clock
    RCC_APB1ENR |= RCC_TIM2_EN;

    // Stop timer during config
    TIM2_CR1 &= ~TIM_CR1_CEN;

    // Set prescaler for 1 MHz
    TIM2_PSC = TIM2_US_PRESCALER;

    // Auto-reload max
    TIM2_ARR = 0xFFFF;

    // Optional safety
    TIM2_SR = 0;               // Clear status
    TIM2_EGR |= (1 << 0);      // Force update
    TIM2_CR1 |= TIM_CR1_ARPE;  // Enable auto-reload

    TIM2_CNT = 0;
    TIM2_CR1 |= TIM_CR1_CEN;   // Start timer
}

void TIM2_Delay_us(uint32_t us)
{
  TIM2_CR1 &= ~TIM_CR1_CEN;
  TIM2_CNT = 0;
  TIM2_CR1 |= TIM_CR1_CEN;
  while (TIM2_CNT < us);
  TIM2_CR1 &= ~TIM_CR1_CEN;
}

void TIM2_StartCounter(void)
{
  TIM2_CR1 &= ~TIM_CR1_CEN;
  TIM2_CNT = 0;
  TIM2_CR1 |= TIM_CR1_CEN;
  TIM2_CR1 |= TIM_CR1_CEN;
}

void TIM2_ResetCounter(void)
{
  TIM2_CR1 &= ~TIM_CR1_CEN;
  TIM2_CNT = 0;
  TIM2_CR1 |= TIM_CR1_CEN;
}

uint32_t TIM2_GetCounter(void)
{
  return TIM2_CNT;
}
