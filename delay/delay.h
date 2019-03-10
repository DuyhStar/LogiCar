/*
 * delay.h
 *
 *  Created on: 2018Äê1ÔÂ26ÈÕ
 *      Author: wk
 */

#ifndef DELAY_DELAY_H_
#define DELAY_DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

extern void delay_ms(uint32_t n);
extern void delay_s(uint32_t n);
extern void delay_ns(uint32_t n);

#endif /* DELAY_DELAY_H_ */
