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
#include <stdint.h>
#include <stdlib.h>

struct HC_SR04_Config_tag
{
  GPIO_e gpioBase;
  uint8_t triggerPin;
  uint8_t echoPin;
};



/*----------------Accessible Functions----------------------*/

HC_SR04_Config_t* HC_SR04_Init(GPIO_e gpio_base, uint8_t trigger_pin, uint8_t echo_pin)
{
  HC_SR04_Config_t* psensorConfig = malloc(sizeof(HC_SR04_Config_t));
  psensorConfig->gpioBase   = gpio_base;
  psensorConfig->triggerPin = trigger_pin;
  psensorConfig->echoPin    = echo_pin;
  return psensorConfig;
}


uint32_t measureEchoTime(HC_SR04_Config_t* psensorConfig)
{
    GPIO_Config_t* trigger_pin = GPIO_Init(psensorConfig->gpioBase, psensorConfig->triggerPin, OUTPUT, GPIO_RESET);
    GPIO_Config_t* echo_pin    = GPIO_Init(psensorConfig->gpioBase, psensorConfig->echoPin, INPUT, GPIO_RESET);
    TIM2_Delay_Init();

    // Send 10us pulse to trigger
    GPIO_Write(trigger_pin, GPIO_RESET);
    TIM2_Delay_us(2);

    GPIO_Write(trigger_pin, GPIO_SET);
    TIM2_Delay_us(10);  // 10 us pulse
    GPIO_Write(trigger_pin, GPIO_RESET);

    uint32_t timeout = 30000;
    while (!GPIO_Read(echo_pin)) {
        if (--timeout == 0) {
            GPIO_deInit(trigger_pin);
            GPIO_deInit(echo_pin);
            return 0xFFFFFFFF; // timeout error
        }
    }

    // Start measuring using timer counter
    TIM2_CNT = 0;
    while (GPIO_Read(echo_pin)) {
        if (TIM2_CNT > 30000) {  // 30ms timeout
            GPIO_deInit(trigger_pin);
            GPIO_deInit(echo_pin);
            return 0xFFFFFFFF;
        }
    }

    uint32_t echo_time_us = TIM2_CNT;

    GPIO_deInit(trigger_pin);
    GPIO_deInit(echo_pin);

    return echo_time_us;  // in microseconds
}


float getDistanceCm(HC_SR04_Config_t* psensorConfig)
{
    uint32_t echoTime = measureEchoTime(psensorConfig);
    if (echoTime == 0xFFFFFFFF)
    {
        return -1.0f;
    }
    // Speed of sound = 343 m/s = 0.0343 cm/us
    float distance_cm = (echoTime * 0.0343f) / 2.0f;
    return distance_cm;
}



void HC_SR04_deInit(HC_SR04_Config_t* psensorConfig)
{
  free(psensorConfig);
}
