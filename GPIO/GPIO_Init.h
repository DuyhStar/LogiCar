/*
 * GPIO_Init.h
 *
 *  Created on: 2018Äê4ÔÂ6ÈÕ
 *      Author: DuYihao
 */

#ifndef GPIO_GPIO_INIT_H_
#define GPIO_GPIO_INIT_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "delay.h"

#define RED1   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
#define BLUE1  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
#define GREEN1 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
#define BEEP1  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
#define RED0   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
#define BLUE0  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
#define GREEN0 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
#define BEEP0  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);

void    PF123_RGB_Init(void);
void    PF1_Red_Init(void);
void    PF2_Blue_Init(void);
void    PF3_Green_Init(void);

void    key1_init();
uint8_t Key1_Read();
void    system_waitKey();

#endif /* GPIO_GPIO_INIT_H_ */
