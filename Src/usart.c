/*
 * usart.c
 *
 *  Created on: Jun 24, 2025
 *      Author: chait
 */
#include "usart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#define SYS_FREQ         16000000
#define PERIPHERAL_CLOCK SYS_FREQ
#define BAUD_RATE        115200

void usart2_init(void)
{
  //Allow clock access to usart2 peripheral
  RCC_APB1ENR |= RCC_USART2_EN;

  //Set A2 and A3 for usart
  GPIO_ConfigUSART2();

  //configure baudrate
  usart_set_baudrate(PERIPHERAL_CLOCK, BAUD_RATE);


  //enable tx and rx transfer function in cr1
  USART2_CR1 |= CR1_TE;
  USART2_CR1 |= CR1_RE;

  //enable
  USART2_CR1 |= CR1_UE;

}

void usart2_write(uint8_t data)
{
  while(!(USART2_SR & SR_TXE));
  USART2_DR = data;
}


uint8_t usart2_read(void)
{
  while(!(USART2_SR & SR_RXNE));
  return USART2_DR;
}

void usart_set_baudrate(uint32_t peripheral_clock, uint32_t baudrate)
{
  USART2_BRR = ((peripheral_clock + (baudrate/2)) / baudrate);
}

void usart2_printf(const char *fmt, ...)
{
  char buffer[128];  // You can adjust size
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);  // Format string
  va_end(args);

  for (int i = 0; buffer[i] != '\0'; i++)
  {
    usart2_write((uint8_t)buffer[i]);
  }
}

