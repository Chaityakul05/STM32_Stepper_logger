/*
 * usart.h
 *
 *  Created on: Jun 24, 2025
 *      Author: chait
 */

#ifndef USART_H_
#define USART_H_

#include "base.h"
#include <stdint.h>

#define USART2_CR1_OFFSET  (0x0C)
#define USART2_CR1         (*(volatile uint32_t*)(USART2_PERIPHERAL + USART2_CR1_OFFSET))

#define USART2_BRR_OFFSET  (0x08)
#define USART2_BRR         (*(volatile uint32_t*)(USART2_PERIPHERAL + USART2_BRR_OFFSET))

#define USART2_SR_OFFSET   (0x00)
#define USART2_SR          (*(volatile uint32_t*)(USART2_PERIPHERAL + USART2_SR_OFFSET))

#define USART2_DR_OFFSET   (0x04)
#define USART2_DR          (*(volatile uint32_t*)(USART2_PERIPHERAL + USART2_DR_OFFSET))

#define RCC_APB1ENR_OFFSET (0x1C)
#define RCC_APB1ENR        (*(volatile uint32_t*)(RCC_PERIPHERAL + RCC_APB1ENR_OFFSET))

#define CR1_UE            (1 << 13)
#define CR1_RE            (1 << 2)
#define CR1_TE            (1 << 3)

#define SR_RXNE           (1 << 5)
#define SR_TXE            (1 << 7)

#define RCC_USART2_EN     (1 << 17)


/*Function Prototypes*/
void usart2_init(void);
void usart2_write(uint8_t data);
uint8_t usart2_read(void);
void usart2_printf(const char *fmt, ...);
void usart_set_baudrate(uint32_t peripheral_clock, uint32_t baudrate);

#endif /* USART_H_ */
