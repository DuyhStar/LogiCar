/*
 * sensor.c
 *
 *  Created on: 2018年7月13日
 *      Author: D
 */
#include "sensor.h"

/*    前右：PA2
 *    前左：PA3
 *    中中：PA4
 *    后左：PA5
 *    后右：PE3
 */

void black_detect_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIODirModeSet(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

int8_t front_left_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3);
    if( (ui32state&GPIO_PIN_3) ==  GPIO_PIN_3)
        return 1;
    else
        return 0;
}
int8_t front_right_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
    if( (ui32state&GPIO_PIN_2) ==  GPIO_PIN_2)
        return 1;
    else
        return 0;
}

int8_t middle_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
    if( (ui32state&GPIO_PIN_4) ==  GPIO_PIN_4)
        return 1;
    else
        return 0;
}

int8_t back_left_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
    if( (ui32state&GPIO_PIN_5) ==  GPIO_PIN_5)
        return 1;
    else
        return 0;
}
int8_t back_right_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);
    if( (ui32state&GPIO_PIN_3) ==  GPIO_PIN_3)
        return 1;
    else
        return 0;
}

void   UART1_angle_mpu6050_init(uint32_t Baud)
{
    UART1_Init(Baud);
}
void   MPU6050_correct()
{
    UARTCharPut(UART1_BASE, 0xA5);
    UARTCharPut(UART1_BASE, 0x54);
    UARTCharPut(UART1_BASE, 0xA5);
    UARTCharPut(UART1_BASE, 0x55);
}
//void SuperWave_Init(void)
//{
//    UART1_Init(9600);
//}
//void SuperWave_Trig(void)
//{
//    UARTCharPutNonBlocking(UART1_BASE, 0x55);
//}


