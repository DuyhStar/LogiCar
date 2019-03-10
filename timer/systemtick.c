/*
 * systemtick.c
 *
 *  Created on: 2019��3��10��
 *      Author: DuYihao
 */
#include "systemtick.h"


void SysTick_Init_ms(uint8_t ui8IntTime)
{
    SysTickPeriodSet((SysCtlClockGet()/1000)*ui8IntTime);

    SysTickIntRegister(IntHandler_SysTick);
    SysTickIntEnable();
    //SysTickEnable();
    SysTickDisable();
    IntMasterDisable();
}

