/*
 * ServoCtl.h
 *
 *  Created on: 2018年9月21日
 *      Author: admin
 */

#ifndef SERVOCTL_SERVOCTL_H_
#define SERVOCTL_SERVOCTL_H_

#include <stdint.h>
#include <stdbool.h>
#include "PWM_Init.h"
#include "I2C_Init.h"
#include "PCA9685.h"
#include "delay.h"

void servo_init(uint16_t *initAngle);

void pca9685_reg_write(uint8_t reg_add, uint8_t data);
void pca9685_reg_read(uint8_t reg_add, uint8_t *data);

void PCA9685_set_freq(float freq);
void PCA9685_set_PWM(uint8_t num, uint16_t on, uint16_t off);
void PCA9685_pulse_us_set(uint8_t num, uint16_t us);

//手动设置舵机位置
void hand_set_servo();

/*主要通过这个函数操作舵机
 * angle的值可以在 1000-2000 之间
 * 即脉宽为1.0ms-2ms,1.5ms是中间位置
 */
void servo_n_angle_set(uint8_t n, uint16_t angle);
void servo_all_update(uint16_t *val);

/*
 * 机械臂运动路径
 * */
void place(uint8_t pos);

void place_1();
void place_2();
void place_3();

void take(uint8_t n);

void take_1();
void take_2();
void take_3();

void return_pos();

#endif /* SERVOCTL_SERVOCTL_H_ */

