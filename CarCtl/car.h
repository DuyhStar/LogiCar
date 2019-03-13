/*
 * car.h
 *
 *  Created on: 2018��7��13��
 *      Author: D
 */

#ifndef CARCTL_CAR_H_
#define CARCTL_CAR_H_

#include "PWM_Init.h"
#include "delay.h"

//С����������PWM����ʼ��
void car_init();

//ǰ������
void car_forward(uint16_t speed);
void car_back(uint16_t speed);

//ǰ�����˵���ת��ת
void car_turn_left(uint16_t range);
void car_turn_right(uint16_t range);

//ǰ�����˲�Ѳ��
void car_forward_patrol_line();
void car_back_patrol_line();

//ԭ������ת90��
void car_turn_left_90_degree();
void car_turn_right_90_degree();

//ǰ������n������
void car_forward_goto_n_black_line(uint8_t n);
void car_back_goto_n_black_line(uint8_t n);

//�����һ��λ��
void car_begin_goto_first_pos();

//һЩֹͣ����
void car_stop();
void car_stop_forward();
void car_stop_back();
void car_stop_turn_right();
void car_stop_turn_left();

#endif /* CARCTL_CAR_H_ */


