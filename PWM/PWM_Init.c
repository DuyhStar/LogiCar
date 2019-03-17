/*
 * PWM_Init.c
 *
 *  Created on: 2018年7月7日
 *      Author: D
 */
/*
 * PWM0_0   PB6
 * PWM0_1   PB7
 * PWM0_2   PB4
 * PWM0_3   PB5
 * PWM0_4   PE4
 * PWM0_5   PE5
 *
 * PWM1_0   PD0
 * PWM1_1   PD1
 * PWM1_2   PA6
 * PWM1_3   PA7
 * PWM1_4   PF0
 *
 */
#include "PWM_Init.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#define PWM0_CLOCK_DIV SYSCTL_PWMDIV_1
#define PWM1_CLOCK_DIV SYSCTL_PWMDIV_16
#define DIV 1
#define DIV_1 16

void PWM0_0_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    SysCtlPWMClockSet(PWM0_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SysCtlClockGet()/DIV/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100);

    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}
void PWM0_1_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    SysCtlPWMClockSet(PWM0_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SysCtlClockGet()/DIV/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100);

    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}
void PWM0_2_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    SysCtlPWMClockSet(PWM0_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, SysCtlClockGet()/DIV/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100);

    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}
void PWM0_3_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    SysCtlPWMClockSet(PWM0_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PB5_M0PWM3);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, SysCtlClockGet()/DIV/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100);

    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}
void PWM0_4_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    SysCtlPWMClockSet(PWM0_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PE4_M0PWM4);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/DIV/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100);

    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
}
void PWM0_5_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    SysCtlPWMClockSet(PWM0_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PE5_M0PWM5);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/DIV/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/100);

    PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
}
//**********************************************************************************************//
//初始化PWM波，用来控制机械臂上舵机运动
//周期:20ms 频率：50Hz
//初始脉冲长短：2ms
//
//舵机角度控制：脉冲1ms-2ms为范围
void PWM1_0_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PD0_M1PWM0);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, SysCtlClockGet()/DIV_1/50);//周期50ms
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}
void PWM1_1_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PD1_M1PWM1);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, SysCtlClockGet()/DIV_1/50);//周期50ms
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
}
void PWM1_2_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PA6_M1PWM2);
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, SysCtlClockGet()/DIV_1/50);//周期50ms
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
}
void PWM1_3_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PA7_M1PWM3);
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_7);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, SysCtlClockGet()/DIV_1/50);//周期50ms
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
}
void PWM1_4_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;//解锁
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;//确认
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;//重新锁定

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PF0_M1PWM4);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, SysCtlClockGet()/DIV_1/50);//周期50ms
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
}
