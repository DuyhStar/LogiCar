/*
 * car.h
 *
 *  Created on: 2018Äê7ÔÂ13ÈÕ
 *      Author: D
 */

#ifndef CARCTL_CAR_H_
#define CARCTL_CAR_H_

#include "PWM_Init.h"
#include "delay.h"

void Car_Init();

void car_patrol_line();
void car_goto_n_black_line(uint8_t n);
void car_turn_left_90_degree();
void car_turn_right_90_degree();

void Car_GoForward(uint16_t speed);
void Car_GoBack(uint16_t speed);
void Car_TurnLeft_Stay(uint16_t range);
void Car_TurnRight_Stay(uint16_t range);

void Car_Stop();

void CarStop_forward();
void CarStop_back();
void CarStop_turnRight();
void CarStop_turnLeft();

#endif /* CARCTL_CAR_H_ */
