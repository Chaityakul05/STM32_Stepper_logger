# 🌀 STM32 Bare-Metal: Stepper Motor + HC-SR04 + USART Logger

This is a simple bare-metal project for the STM32F103C8T6 (Blue Pill) that:
- Rotates a 28BYJ-48 stepper motor step-by-step,
- Measures distance using the HC-SR04 ultrasonic sensor,
- Logs distance readings via USART2.

## 📄 main.c Overview

```c
#include "usart.h"
#include "HC_SR04.h"
#include "StepperMotor.h"

int main(void)
{
  usart2_init();
  usart2_printf("Stepper + Ultrasonic Logger Start\n");

  StepperMotor_Config_t* motor = StepperMotor_Init(GPIO_B, 0, 1, 10, 11, 5);
  HC_SR04_Config_t* sensor = HC_SR04_Init(GPIO_A, 8, 9);

  while (1)
  {
    StepperMotor_StepForward(motor, 1);
    float distance = getDistanceCm(sensor);
    usart2_printf("Distance: %.2f cm\n", distance);
    GPIO_Delay(100000); // Add delay between steps
  }

  StepperMotor_deInit(motor);
  HC_SR04_deInit(sensor);
}


