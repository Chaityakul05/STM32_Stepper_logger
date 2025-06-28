/*
 * StepperMotor.c
 *
 *  Created on: Jun 13, 2025
 *      Author: chait
 */

#include "base.h"
#include "gpio.h"
#include "StepperMotor.h"
#include <stdint.h>
#include <stdlib.h>

/*------------Structure Definition---------------*/
struct StepperMotor_Config_tag
{
  GPIO_Config_t* pin1;
  GPIO_Config_t* pin2;
  GPIO_Config_t* pin3;
  GPIO_Config_t* pin4;
  uint8_t stepDelay;
};

/*--------------Static Functions------------------*/
static void stepSequence(StepperMotor_Config_t* motor, uint8_t step)
{
  static const uint8_t sequence[4][4] =
  {
     {1, 0, 0, 1},
     {1, 0, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0}
  };

    GPIO_Write(motor->pin1, sequence[step][0]);
    GPIO_Write(motor->pin2, sequence[step][1]);
    GPIO_Write(motor->pin3, sequence[step][2]);
    GPIO_Write(motor->pin4, sequence[step][3]);
}

/*------------Accessible Functions-----------------*/
StepperMotor_Config_t* StepperMotor_Init(GPIO_e port, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t delay_ms)
{
  StepperMotor_Config_t* motor = malloc(sizeof(StepperMotor_Config_t));

  motor->pin1 = GPIO_Init(port, p1, OUTPUT, GPIO_RESET);
  motor->pin2 = GPIO_Init(port, p2, OUTPUT, GPIO_RESET);
  motor->pin3 = GPIO_Init(port, p3, OUTPUT, GPIO_RESET);
  motor->pin4 = GPIO_Init(port, p4, OUTPUT, GPIO_RESET);

  motor->stepDelay = delay_ms;

  return motor;
}

void StepperMotor_StepForward(StepperMotor_Config_t* motor, uint16_t steps)
{
  for (uint16_t i = 0; i < steps; i++)
  {
    for (uint8_t s = 0; s < 4; s++)
    {
       stepSequence(motor, s);
       GPIO_Delay(motor->stepDelay * 100);  // Adjust if needed
    }
  }
}

void StepperMotor_StepBackward(StepperMotor_Config_t* motor, uint16_t steps)
{
  for (uint16_t i = 0; i < steps; i++)
  {
    for (int8_t s = 3; s >= 0; s--)
    {
      stepSequence(motor, s);
      GPIO_Delay(motor->stepDelay * 100);
    }
  }
}

void StepperMotor_deInit(StepperMotor_Config_t* motor)
{
  GPIO_deInit(motor->pin1);
  GPIO_deInit(motor->pin2);
  GPIO_deInit(motor->pin3);
  GPIO_deInit(motor->pin4);
  free(motor);
}

