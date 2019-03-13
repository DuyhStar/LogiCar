/*
 * sensor.h
 *
 *  Created on: 2018Äê7ÔÂ13ÈÕ
 *      Author: D
 */

#ifndef EXTERNSENSOR_SENSOR_H_
#define EXTERNSENSOR_SENSOR_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "UART_Init.h"

void   black_detect_init(void);

int8_t front_left_black(void);
int8_t front_right_black(void);

int8_t middle_black(void);

int8_t back_left_black(void);
int8_t back_right_black(void);

void   UART1_angle_mpu6050_init(uint32_t Baud);
void   MPU6050_correct();
//void SuperWave_Init(void);
//void SuperWave_Trig(void);

#endif /* EXTERNSENSOR_SENSOR_H_ */
