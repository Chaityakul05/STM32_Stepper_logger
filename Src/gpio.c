/*
 * gpio.c
 *
 *  Created on: Jun 13, 2025
 *      Author: chait
 */



#include "gpio.h"
#include "base.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct GPIO_Config_tag
{
  GPIO_e gpioTag;
  uint8_t gpioPin;
  GpioMode_e gpioMode;
  GpioState_e gpioState;
};


static volatile uint32_t* getGpioBase(GPIO_e gpioTag)
{
  switch(gpioTag)
  {
  case GPIO_A: return GPIOA_PERIPHERAL;
  case GPIO_B: return GPIOB_PERIPHERAL;
  case GPIO_C: return GPIOC_PERIPHERAL;
  default: return 0;
  }
}

static void enableClock(GPIO_e gpioTag)
{
  switch(gpioTag)
  {
  case GPIO_A: RCC_APB2ENR |= (1U << 2); break;
  case GPIO_B: RCC_APB2ENR |= (1U << 3); break;
  case GPIO_C: RCC_APB2ENR |= (1U << 4); break;
  }
}

static void setGpioState(GPIO_Config_t *pConfig)
{

  volatile uint32_t* gpioBase = getGpioBase(pConfig->gpioTag);

  volatile uint32_t* BSRR = gpioBase + (GPIO_BSRR_OFFSET / 4);

  if(pConfig->gpioState == GPIO_SET)
  {
    *BSRR = (1 << pConfig->gpioPin);
  }
  else
  {
    *BSRR = (1 << (pConfig->gpioPin + 16));
  }

}

static void configGpioPin(GPIO_Config_t *pConfig)
{
  volatile uint32_t* gpioBase = getGpioBase(pConfig->gpioTag);

  uint8_t pin  = pConfig->gpioPin;
  volatile uint32_t* configReg;

  if(pin < 8)
  {
    configReg = gpioBase + (GPIO_CRL_OFFSET / 4);
  }
  else
  {
    configReg = gpioBase + (GPIO_CRH_OFFSET / 4);
     pin -= 8;
  }

  *configReg &= ~(0xF << (pin * 4));

  if(pConfig->gpioMode == OUTPUT)
  {
    *configReg |=  (0x2 << (pin * 4));
  }
  else if(pConfig->gpioMode == INPUT)
  {
    *configReg |= (0x4 << (pin * 4));
  }


}

/*----------------Accessible_functions----------------------*/

GPIO_Config_t *GPIO_Init(GPIO_e gpioTags, uint8_t pinNumber, GpioMode_e gpioMode, GpioState_e gpioStates)
{
  GPIO_Config_t *pConfig = malloc(sizeof(GPIO_Config_t));
  pConfig->gpioTag   = gpioTags;
  pConfig->gpioPin   = pinNumber;
  pConfig->gpioMode  = gpioMode;
  pConfig->gpioState = gpioStates;

  enableClock(pConfig->gpioTag);

  if(pConfig->gpioMode == OUTPUT)
  {
    setGpioState(pConfig);
    configGpioPin(pConfig);
  }
  else
  {
    configGpioPin(pConfig);
  }

  return pConfig;
}

void GPIO_Write(GPIO_Config_t* pConfig, GpioState_e state)
{
  volatile uint32_t* gpio_base = getGpioBase(pConfig->gpioTag);
  volatile uint32_t* BSRR = gpio_base + (GPIO_BSRR_OFFSET / 4);

  if(state == GPIO_SET)
  {
    *BSRR = (1 << pConfig->gpioPin);
  }
  else
  {
    *BSRR = (1 << (pConfig->gpioPin + 16));
  }
}

GpioState_e GPIO_Read(GPIO_Config_t* pConfig)
{
  volatile uint32_t* gpioBase = getGpioBase(pConfig->gpioTag);
  volatile uint32_t* IDR      = gpioBase + (GPIO_IDR_OFFSET / 4);

  if((*IDR) & (1 << pConfig->gpioPin))
  {
    return GPIO_SET;
  }
  else
  {
    return GPIO_RESET;
  }
}

void GPIO_Delay(uint32_t count){
  for(volatile uint32_t i = 0; i < count; i ++){
    //Wait
  }
}

void GPIO_deInit(GPIO_Config_t* pConfig){
  free(pConfig);
}

void GPIO_ConfigUSART2(void) {
    enableClock(GPIO_A);

    volatile uint32_t* gpioBase = getGpioBase(GPIO_A);

    // PA2 (TX) → Alternate function push-pull, output mode 2MHz (MODE=10, CNF=10)
    volatile uint32_t* crl = gpioBase + (GPIO_CRL_OFFSET / 4);
    *crl &= ~(0xF << (2 * 4));             // Clear bits for PA2
    *crl |=  ((0xA) << (2 * 4));           // Set MODE=10, CNF=10

    // PA3 (RX) → Input floating (MODE=00, CNF=01)
    *crl &= ~(0xF << (3 * 4));             // Clear bits for PA3
    *crl |=  ((0x4) << (3 * 4));           // Set MODE=00, CNF=01
}



