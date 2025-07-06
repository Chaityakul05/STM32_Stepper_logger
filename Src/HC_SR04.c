/*
 * HC_SR04.c
 *
 *  Created on: Jun 28, 2025
 *      Author: chait
 */

#include "base.h"
#include "gpio.h"
#include "HC_SR04.h"
#include "tim_delay.h"
#include "dwt_timer.h"
#include "usart.h"
#include <stdint.h>
#include <stdlib.h>

struct HC_SR04_Config_tag
{
  GPIO_e gpioBase;
  uint8_t triggerPin;
  uint8_t echoPin;
  GPIO_Config_t* ptrigger_pin;
  GPIO_Config_t* pecho_pin;
};



/*----------------Accessible Functions----------------------*/

HC_SR04_Config_t* HC_SR04_Init(GPIO_e gpio_base, uint8_t trigger_pin, uint8_t echo_pin)
{
  HC_SR04_Config_t* psensorConfig = malloc(sizeof(HC_SR04_Config_t));
  psensorConfig->gpioBase    = gpio_base;
  psensorConfig->triggerPin  = trigger_pin;
  psensorConfig->echoPin     = echo_pin;
  psensorConfig->ptrigger_pin =  GPIO_Init(psensorConfig->gpioBase, psensorConfig->triggerPin, OUTPUT, GPIO_RESET);
  psensorConfig->pecho_pin    =  GPIO_Init(psensorConfig->gpioBase, psensorConfig->echoPin, INPUT, GPIO_RESET);
  return psensorConfig;
}


uint32_t measureEchoTime(HC_SR04_Config_t* psensorConfig)
{
    TIM2_Delay_Init();  // Initialize TIM2 for 1MHz counting
    //usart2_init();

    // Trigger the ultrasonic pulse
    GPIO_Write(psensorConfig->ptrigger_pin, GPIO_RESET);
    TIM2_Delay_us(2);

    GPIO_Write(psensorConfig->ptrigger_pin, GPIO_SET);
    TIM2_Delay_us(10);
    GPIO_Write(psensorConfig->ptrigger_pin, GPIO_RESET);

    // Wait for ECHO to go HIGH
    TIM2_ResetCounter();
    TIM2_StartCounter();
    while (GPIO_Read(psensorConfig->pecho_pin) == GPIO_RESET)
    {
        //usart2_printf("Echo is low\n");
        if (TIM2_CNT > 60000)  // 30 ms timeout
            return 0xFFFFFFFF;
    }

    // Record start time
    uint32_t echo_start = TIM2_GetCounter();
    //usart2_printf("Start-%d\n", echo_start);

    // Wait for ECHO to go LOW
    while (GPIO_Read(psensorConfig->pecho_pin) == GPIO_SET)
    {
      //usart2_printf("Echo is High\n");
      if ((TIM2_GetCounter() - echo_start) > 60000)  // max echo pulse width
          return 0xFFFFFFFF;
    }

    // Record end time
    uint32_t echo_end = TIM2_GetCounter();
    //usart2_printf("End-%d\n", echo_end);

    return (echo_end - echo_start);  // pulse duration in µs
}


uint32_t getDistanceCm(HC_SR04_Config_t* psensorConfig)
{
    uint32_t echoTime = measureEchoTime(psensorConfig);
    if (echoTime == 0xFFFFFFFF)
    {
        return -1;
    }
    // Speed of sound = 343 m/s = 0.0343 cm/us
    uint32_t distance_cm = (echoTime * 343) / 20000;
    return distance_cm;
}

int getFilteredDistanceInt(HC_SR04_Config_t* psensorConfig, int samples)
{
  int sum = 0;
  int valid_count = 0;

  for (int i = 0; i < samples; i++)
  {
    uint32_t dist = getDistanceCm(psensorConfig);
    if (dist >= 0 && dist < 400)
    {
      sum += (int)dist;
      valid_count++;
    }

    TIM2_Delay_us(60000);
  }

  if (valid_count == 0)
     return -1;

  return sum / valid_count;
}



void HC_SR04_deInit(HC_SR04_Config_t* psensorConfig)
{
  free(psensorConfig->ptrigger_pin);
  free(psensorConfig->pecho_pin);
  free(psensorConfig);
}
