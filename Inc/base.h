/*
 * base.h
 *
 *  Created on: Jun 13, 2025
 *      Author: chait
 */

/*
 * base.h
 *
 *  Created on: Jun 13, 2025
 *      Author: chait
 */

#ifndef BASE_H_
#define BASE_H_

#include <stdint.h>

#define PERIPHERAL_BASE              (0x40000000)

#define APB1_PERIPHERAL_OFFSET       (0x00000000)
#define APB1_PERIPHERAL              (PERIPHERAL_BASE + APB1_PERIPHERAL_OFFSET)

#define USART2_PERIPHERAL_OFFSET     (0x00004400)
#define USART2_PERIPHERAL            (APB1_PERIPHERAL + USART2_PERIPHERAL_OFFSET)

#define APB2_PERIPHERAL_OFFSET       (0x00010000)
#define APB2_PERIPHERAL              (PERIPHERAL_BASE + APB2_PERIPHERAL_OFFSET)

#define AHB_PERIPHERAL_OFFSET        (0x00020000)
#define AHB_PERIPHERAL               (PERIPHERAL_BASE + AHB_PERIPHERAL_OFFSET)

#define GPIOA_PERIPHERAL_OFFSET      (0x00000800)
#define GPIOA_PERIPHERAL             ((volatile uint32_t*)(APB2_PERIPHERAL + GPIOA_PERIPHERAL_OFFSET))

#define GPIOB_PERIPHERAL_OFFSET      (0x00000C00)
#define GPIOB_PERIPHERAL             ((volatile uint32_t*)(APB2_PERIPHERAL + GPIOB_PERIPHERAL_OFFSET))

#define GPIOC_PERIPHERAL_OFFSET      (0x00001000)
#define GPIOC_PERIPHERAL             ((volatile uint32_t*)(APB2_PERIPHERAL + GPIOC_PERIPHERAL_OFFSET))

#define RCC_PERIPHERAL_OFFSET        (0x00001000)
#define RCC_PERIPHERAL               (AHB_PERIPHERAL + RCC_PERIPHERAL_OFFSET)

#endif /* BASE_H_ */


