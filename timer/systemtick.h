/*
 * systemtick.h
 *
 *  Created on: 2019Äê3ÔÂ10ÈÕ
 *      Author: DuYihao
 */

#ifndef TIMER_SYSTEMTICK_H_
#define TIMER_SYSTEMTICK_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

void SysTick_Init_ms(uint8_t ui8IntTime);
void IntHandler_SysTick(void);

#endif /* TIMER_SYSTEMTICK_H_ */
