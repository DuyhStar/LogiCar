/*
 * GPIO_Init.c
 *
 *  Created on: 2018Äê4ÔÂ6ÈÕ
 *      Author: DuYihao
 */
#include "GPIO_Init.h"

void PF123_RGB_Init(void)
{
    PF1_Red_Init();
    PF3_Green_Init();
    PF2_Blue_Init();
}
void PF1_Red_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
}
void PF2_Blue_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
}
void PF3_Green_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}

void Key1_init()
{
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

uint8_t Key1_Read()
{
    uint8_t s;
    s = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if(s != GPIO_PIN_4)
        return 1;
    else
        return 0;
}

void system_waitKey()
{
    while(1)
    {
        if(Key1_Read() == 1)
        {
            delay_ms(20);
            if(Key1_Read() == 1)
                break;
        }
    }
}
