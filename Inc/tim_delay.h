/*
 * tim_delay.h
 *
 *  Created on: Jul 2, 2025
 *      Author: chait
 */

#ifndef TIM_DELAY_H_
#define TIM_DELAY_H_

#include <stdint.h>
#include "base.h"

/*------------- Base Address Macros --------------*/
#define TIM2_PERIPHERAL_OFFSET       (0x00000000)
#define TIM2_PERIPHERAL              (APB1_PERIPHERAL + TIM2_PERIPHERAL_OFFSET)

/*------------- TIM2 Register Offsets ------------*/
#define TIM2_CR1_OFFSET              (0x00)
#define TIM2_CNT_OFFSET              (0x24)
#define TIM2_PSC_OFFSET              (0x28)
#define TIM2_ARR_OFFSET              (0x2C)

/*------------- TIM2 Register Macros -------------*/
#define TIM2_CR1   (*(volatile uint32_t*)(TIM2_PERIPHERAL + TIM2_CR1_OFFSET))
#define TIM2_CNT   (*(volatile uint32_t*)(TIM2_PERIPHERAL + TIM2_CNT_OFFSET))
#define TIM2_PSC   (*(volatile uint32_t*)(TIM2_PERIPHERAL + TIM2_PSC_OFFSET))
#define TIM2_ARR   (*(volatile uint32_t*)(TIM2_PERIPHERAL + TIM2_ARR_OFFSET))

/*------------- RCC Macros ------------------------*/
#define RCC_APB1ENR_OFFSET           (0x1C)
#define RCC_APB1ENR                 (*(volatile uint32_t*)(RCC_PERIPHERAL + RCC_APB1ENR_OFFSET))
#define RCC_TIM2_EN                 (1 << 0)

/*------------- CR1 Bit Macros --------------------*/
#define TIM_CR1_CEN                 (1 << 0)  // Counter enable

/*------------- Clock Frequency -------------------*/
#define SYS_FREQ                    8000000UL  // 16 MHz
#define TIM2_US_PRESCALER          ((SYS_FREQ / 1000000UL) - 1)

/*------------- Function Prototypes ---------------*/
void TIM2_Delay_Init(void);
void TIM2_Delay_us(uint32_t us);


#endif /* TIM_DELAY_H_ */
