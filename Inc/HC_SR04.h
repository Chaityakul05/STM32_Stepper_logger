/*
 * HC_SR04.h
 *
 *  Created on: Jun 28, 2025
 *      Author: chait
 */

#ifndef HC_SR04_H_
#define HC_SR04_H_

#include "base.h"
#include <stdint.h>

/*--------------Structure Definition------------------*/
typedef struct HC_SR04_Config_tag HC_SR04_Config_t;



/*--------------Function Prototypes------------------*/
HC_SR04_Config_t* HC_SR04_Init(GPIO_e gpio_base, uint8_t trigger_pin, uint8_t echo_pin);
uint32_t measureEchoTime(HC_SR04_Config_t* psensorConfig);
uint32_t getDistanceCm(HC_SR04_Config_t* psensorConfig);
int getFilteredDistanceInt(HC_SR04_Config_t* psensorConfig, int samples);
void HC_SR04_deInit(HC_SR04_Config_t* psensorConfig);


#endif /* HC_SR04_H_ */
