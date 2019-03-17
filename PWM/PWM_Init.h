/*
 * PWM_Init.h
 *
 *  Created on: 2018Äê7ÔÂ7ÈÕ
 *      Author: D
 */

#ifndef PWM_INIT_H_
#define PWM_INIT_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

void PWM0_0_Init();
void PWM0_1_Init();
void PWM0_2_Init();
void PWM0_3_Init();
void PWM0_4_Init();
void PWM0_5_Init();

void PWM1_0_Init();
void PWM1_1_Init();
void PWM1_2_Init();
void PWM1_3_Init();
void PWM1_4_Init();

#endif /* PWM_INIT_H_ */


