/*
 * PWM_Init.h
 *
 *  Created on: 2018年7月7日
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

//初始化PWM输出,频率 50 Hz,占空比 10.0 %
extern void PWM0_0_Init(void);
extern void PWM0_1_Init(void);
extern void PWM0_2_Init(void);
extern void PWM0_3_Init(void);
extern void PWM0_4_Init(void);
extern void PWM0_5_Init(void);

extern void PWM1_0_Init(void);
extern void PWM1_1_Init(void);
extern void PWM1_2_Init(void);
extern void PWM1_3_Init(void);

#endif /* PWM_INIT_H_ */


