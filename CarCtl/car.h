/*
 * car.h
 *
 *  Created on: 2018年7月13日
 *      Author: D
 */

#ifndef CARCTL_CAR_H_
#define CARCTL_CAR_H_

#include "PWM_Init.h"
#include "delay.h"

//小车所用驱动PWM波初始化
void car_init();

//前进后退
void car_forward(uint16_t speed);
void car_back(uint16_t speed);

//前进后退的左转右转
void car_turn_left(uint16_t range);
void car_turn_right(uint16_t range);

//前进后退并巡线
void car_forward_patrol_line();
void car_back_patrol_line();

//原地左右转90度
void car_turn_left_90_degree();
void car_turn_right_90_degree();

//前进后退n个黑线
void car_forward_goto_n_black_line(uint8_t n);
void car_back_goto_n_black_line(uint8_t n);

//到达第一个位置
void car_begin_goto_first_pos();

//一些停止函数
void car_stop();
void car_stop_forward();
void car_stop_back();
void car_stop_turn_right();
void car_stop_turn_left();

#endif /* CARCTL_CAR_H_ */


