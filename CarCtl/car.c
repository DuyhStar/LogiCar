/*
 * cal.c
 *
 *  Created on: 2018年7月13日
 *      Author: D
 */
#include "car.h"
#include "driverlib/systick.h"
#include "sensor.h"

//小车所用驱动PWM波初始化
void car_init()
{
    PWM0_0_Init();
    PWM0_1_Init();
    PWM0_2_Init();
    PWM0_3_Init();
    car_stop();
}

//前进
void car_back(uint16_t speed)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}

//后退
void car_forward(uint16_t speed)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 1);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}

//前进后退的左转右转(左右转对于前后来说其实一样)
void car_turn_left(uint16_t range)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 1);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}
void car_turn_right(uint16_t range)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}

//前进后退并巡线
void car_forward_patrol_line()
{
    extern int forward_speed;
    extern int turn_speed;

    if( front_right_black() && front_left_black() )
        car_forward(forward_speed);
    else if(front_right_black())
        car_turn_right(turn_speed);
    else if(front_left_black())
        car_turn_left(turn_speed);
    else
        car_forward(forward_speed);
}
void car_back_patrol_line()
{
    extern int forward_speed;
    extern int turn_speed;

    if( back_right_black() && back_left_black() )
        car_back(forward_speed);
    else if(back_right_black())
        car_turn_right(turn_speed);
    else if(back_left_black())
        car_turn_left(turn_speed);
    else
        car_back(forward_speed);
}
void car_forward_patrol_line_inside()
{
    extern int forward_speed;
    extern int turn_speed;

    int8_t left_black  = front_left_black()  || front_middle_left_black();
    int8_t right_black = front_right_black() || front_middle_right_black();

    if( left_black && right_black )
        car_forward(forward_speed);
    else if(right_black)
        car_turn_right(turn_speed);
    else if(left_black)
        car_turn_left(turn_speed);
    else
        car_forward(forward_speed);
}
void car_back_patrol_line_inside()
{
    extern int forward_speed;
    extern int turn_speed;

    int8_t left_black  = back_middle_left_black();
    int8_t right_black = back_right_black();

    if( left_black && right_black )
        car_back(forward_speed);
    else if(right_black)
        car_turn_right(turn_speed);
    else if(left_black)
        car_turn_left(turn_speed);
    else
        car_back(forward_speed);
}

//原地左右转90度
void car_turn_left_90_degree()
{
    extern int turn_speed;
    car_turn_left(turn_speed);
    delay_s(1);
    while(1){
        if(front_right_black()){
            car_stop_turn_left();
            break;
        }
    }
}
void car_turn_right_90_degree()
{
    extern int turn_speed;
    car_turn_right(turn_speed);
    delay_s(1);
    while(1){
        if(back_left_black()){
            car_stop_turn_right();
            break;
        }
    }
}

//前进后退n个黑线
void car_forward_goto_n_black_line(uint8_t n)
{
    extern uint8_t count_enter;//全局变量

    SysTickEnable();
    uint8_t count = 0;
    while(1)
    {
        car_forward_patrol_line();

        //每隔0.5秒触发一次黑线检测
        if(middle_black()&&(count_enter == 1)){
            count++;
            count_enter = 0;
            SysTickEnable();
        }

        //经过了n条黑线
        if(count == n){
            SysTickDisable();
            count_enter = 1;
            car_stop();
            car_stop_forward();
            break;
        }
    }
}
void car_back_goto_n_black_line(uint8_t n)
{
    extern uint8_t count_enter;//全局变量

    SysTickEnable();
    uint8_t count = 0;
    while(1)
    {
        car_back_patrol_line();

        //每隔0.5秒触发一次黑线检测
        if(middle_black()&&(count_enter == 1)){
            count++;
            count_enter = 0;
            SysTickEnable();
        }

        //经过了n条黑线
        if(count == n){
            SysTickDisable();
            count_enter = 1;
            car_stop_back();
            break;
        }
    }
}
void car_forward_goto_n_black_line_inside(uint8_t n)
{
    extern uint8_t count_enter;//全局变量

    SysTickEnable();
    uint8_t count = 0;
    while(1)
    {
        car_forward_patrol_line_inside();

        //每隔0.5秒触发一次黑线检测
        if(middle_black()&&(count_enter == 1)){
            count++;
            count_enter = 0;
            SysTickEnable();
        }

        //经过了n条黑线
        if(count == n){
            SysTickDisable();
            count_enter = 1;
            car_stop();
            car_stop_forward();
            break;
        }
    }
}
void car_back_goto_n_black_line_inside(uint8_t n)
{
    extern uint8_t count_enter;//全局变量

    SysTickEnable();
    uint8_t count = 0;
    while(1)
    {
        car_back_patrol_line_inside();

        //每隔0.5秒触发一次黑线检测
        if(middle_black()&&(count_enter == 1)){
            count++;
            count_enter = 0;
            SysTickEnable();
        }

        //经过了n条黑线
        if(count == n){
            SysTickDisable();
            count_enter = 1;
            car_stop_back();
            break;
        }
    }
}

//到达第一个位置
void car_begin_goto_first_pos()
{
    extern int forward_speed;
    extern int turn_speed;

    car_forward(forward_speed);
    while(!middle_black())
        ;
    car_stop_forward();
    delay_s(1);


    car_turn_right(turn_speed);
    while(!front_left_black())
        ;
    car_stop();
}

//一些停止函数
void car_stop(void)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 0);
}

void car_stop_forward()
{
    car_back(50);
    delay_ms(100);
    car_stop();
}

void car_stop_back()
{
    car_forward(50);
    delay_ms(100);
    car_stop();
}

void car_stop_turn_right()
{
    car_turn_left(50);
    delay_ms(100);
    car_stop();
}

void car_stop_turn_left()
{
    car_turn_right(50);
    delay_ms(100);
    car_stop();
}


