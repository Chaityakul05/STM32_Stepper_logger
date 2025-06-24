/*
 * gpio.h
 *
 *  Created on: Jun 13, 2025
 *      Author: chait
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "base.h"
#include <stdint.h>

/*---------------- RCC ------------------*/
#define RCC_APB2ENR_OFFSET  (0x18)
#define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_PERIPHERAL + RCC_APB2ENR_OFFSET))

/*---------------- GPIO Register Offsets ----------------*/
#define GPIO_CRL_OFFSET   (0x00)
#define GPIO_CRH_OFFSET   (0x04)
#define GPIO_ODR_OFFSET   (0x0C)
#define GPIO_BSRR_OFFSET  (0x10)
#define GPIO_BRR_OFFSET   (0x14)

/*---------------- GPIOA Registers ----------------*/
#define GPIOA_CRL   (*(volatile uint32_t*)(GPIOA_PERIPHERAL + GPIO_CRL_OFFSET))
#define GPIOA_CRH   (*(volatile uint32_t*)(GPIOA_PERIPHERAL + GPIO_CRH_OFFSET))
#define GPIOA_ODR   (*(volatile uint32_t*)(GPIOA_PERIPHERAL + GPIO_ODR_OFFSET))
#define GPIOA_BSRR  (*(volatile uint32_t*)(GPIOA_PERIPHERAL + GPIO_BSRR_OFFSET))
#define GPIOA_BRR   (*(volatile uint32_t*)(GPIOA_PERIPHERAL + GPIO_BRR_OFFSET))

/*---------------- GPIOB Registers ----------------*/
#define GPIOB_CRL   (*(volatile uint32_t*)(GPIOB_PERIPHERAL + GPIO_CRL_OFFSET))
#define GPIOB_CRH   (*(volatile uint32_t*)(GPIOB_PERIPHERAL + GPIO_CRH_OFFSET))
#define GPIOB_ODR   (*(volatile uint32_t*)(GPIOB_PERIPHERAL + GPIO_ODR_OFFSET))
#define GPIOB_BSRR  (*(volatile uint32_t*)(GPIOB_PERIPHERAL + GPIO_BSRR_OFFSET))
#define GPIOB_BRR   (*(volatile uint32_t*)(GPIOB_PERIPHERAL + GPIO_BRR_OFFSET))

/*---------------- GPIOC Registers ----------------*/
#define GPIOC_CRL   (*(volatile uint32_t*)(GPIOC_PERIPHERAL + GPIO_CRL_OFFSET))
#define GPIOC_CRH   (*(volatile uint32_t*)(GPIOC_PERIPHERAL + GPIO_CRH_OFFSET))
#define GPIOC_ODR   (*(volatile uint32_t*)(GPIOC_PERIPHERAL + GPIO_ODR_OFFSET))
#define GPIOC_BSRR  (*(volatile uint32_t*)(GPIOC_PERIPHERAL + GPIO_BSRR_OFFSET))
#define GPIOC_BRR   (*(volatile uint32_t*)(GPIOC_PERIPHERAL + GPIO_BRR_OFFSET))

/*---------------- Enum Definitions ----------------*/
typedef enum
{
  GPIO_A = 0,
  GPIO_B,
  GPIO_C,
} GPIO_e;

typedef enum
{
  GPIO_RESET = 0,
  GPIO_SET
} GpioState_e;

/*---------------- Struct Declaration ----------------*/
typedef struct GPIO_Config_tag GPIO_Config_t;

/*---------------- Function Prototypes ----------------*/
GPIO_Config_t* GPIO_Init(GPIO_e gpioTag, uint8_t pinNumber, GpioState_e gpioState);
void GPIO_Write(GPIO_Config_t* pConfig, GpioState_e state);
void GPIO_Delay(uint32_t count);
void GPIO_deInit(GPIO_Config_t* pConfig);
void GPIO_ConfigUSART2(void);
#endif /* GPIO_H_ */
