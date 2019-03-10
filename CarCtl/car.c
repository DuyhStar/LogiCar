/*
 * cal.c
 *
 *  Created on: 2018年7月13日
 *      Author: D
 */
#include "car.h"
#include "driverlib/systick.h"
#include "sensor.h"

void Car_Init(void)
{
    PWM0_0_Init();
    PWM0_1_Init();
    PWM0_2_Init();
    PWM0_3_Init();
    Car_Stop();
}

void car_patrol_line()
{
    extern int forward_speed;
    extern int turn_speed;

    if( RightBlack()&&LeftBlack() ){
        Car_GoForward(forward_speed);
    }
    else if(RightBlack()){
        Car_TurnRight_Stay(turn_speed);
    }
    else if(LeftBlack()){
        Car_TurnLeft_Stay(turn_speed);
    }
    else{
        Car_GoForward(forward_speed);
    }
}

void car_goto_n_black_line(uint8_t n)
{
    extern uint8_t count_enter;//全局变量

    SysTickEnable();
    while(1)
    {
        uint8_t count = 0;
        car_patrol_line();

        //每隔一秒触发一次黑线检测
        if(SideBlack()&&(count_enter == 1)){
            count++;
            count_enter = 0;
            SysTickEnable();
        }

        //经过了n条黑线
        if(count == n){
            SysTickDisable();
            count_enter = 1;
            Car_Stop();
            CarStop_forward();
            break;
        }
    }
}

void Car_GoForward(uint16_t speed)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}

void Car_GoBack(uint16_t speed)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 1);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}

void Car_TurnLeft_Stay(uint16_t range)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 1);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}

void Car_TurnRight_Stay(uint16_t range)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 1);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, range*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100));
}

void Car_Stop(void)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, 0);
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, 0);
}

void CarStop_forward()
{
    Car_GoBack(50);
    delay_ms(100);
    Car_Stop();
}

void CarStop_back()
{
    Car_GoForward(50);
    delay_ms(100);
    Car_Stop();
}

void CarStop_turnRight()
{
    Car_TurnLeft_Stay(50);
    delay_ms(100);
    Car_Stop();
}

void CarStop_turnLeft()
{
    Car_TurnRight_Stay(50);
    delay_ms(100);
    Car_Stop();
}


