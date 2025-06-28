/*
 * StepperMotor.h
 *
 *  Created on: Jun 13, 2025
 *      Author: chait
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#include "gpio.h"
#include <stdint.h>



typedef struct StepperMotor_Config_tag StepperMotor_Config_t;

StepperMotor_Config_t* StepperMotor_Init(GPIO_e port, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t delay_ms);
void StepperMotor_StepForward(StepperMotor_Config_t* motor, uint16_t steps);
void StepperMotor_StepBackward(StepperMotor_Config_t* motor, uint16_t steps);
void StepperMotor_deInit(StepperMotor_Config_t* motor);


#endif /* STEPPERMOTOR_H_ */
