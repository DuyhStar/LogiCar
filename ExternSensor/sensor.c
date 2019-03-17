/*
 * sensor.c
 *
 *  Created on: 2018��7��13��
 *      Author: D
 */
#include "sensor.h"

/*
 *    ǰ�ң�    PA2
 *    ǰ��    PA3
 *    ǰ����PA6
 *    ǰ���ң�PA7
 *    ���У�    PA4
 *    ����    PA5
 *    ���ң�    PE3
 *    ������PC6
 *    �����ң�PC7
 */

void black_detect_init(void)
{
    uint8_t A_Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODirModeSet(GPIO_PORTA_BASE,   A_Pin, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTA_BASE, A_Pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    uint8_t E_Pin = GPIO_PIN_3;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIODirModeSet(GPIO_PORTE_BASE,   E_Pin, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTE_BASE, E_Pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    uint8_t C_Pin = GPIO_PIN_6 | GPIO_PIN_7;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIODirModeSet(GPIO_PORTC_BASE,   C_Pin, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTC_BASE, C_Pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
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

int8_t front_middle_left_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6);
    if( (ui32state&GPIO_PIN_6) ==  GPIO_PIN_6)
        return 1;
    else
        return 0;
}
int8_t front_middle_right_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
    if( (ui32state&GPIO_PIN_7) ==  GPIO_PIN_7)
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
    int32_t ui32state = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
    if( (ui32state&GPIO_PIN_3) ==  GPIO_PIN_3)
        return 1;
    else
        return 0;
}

int8_t back_middle_left_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
    if( (ui32state&GPIO_PIN_6) ==  GPIO_PIN_6)
        return 1;
    else
        return 0;
}
int8_t back_middle_right_black(void)
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7);
    if( (ui32state&GPIO_PIN_7) ==  GPIO_PIN_7)
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


