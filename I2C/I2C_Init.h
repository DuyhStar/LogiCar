/*
 * I2C_Configure.h
 *
 *  Created on: 2018Äê4ÔÂ13ÈÕ
 *      Author: DuYihao
 */
#ifndef I2C_I2C_INIT_H_
#define I2C_I2C_INIT_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/i2c.h"

//I2C Driver
extern void     I2C0_Init(void);
extern void     I2C1_Init(void);

extern uint32_t I2CWriteRegOneByte  (uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr,uint8_t ui8RegData);
extern uint32_t I2CWriteRegMultiByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr,uint8_t *pui8RegData,uint32_t ui32WriteCount);
extern uint32_t I2CReadRegOneByte   (uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr,uint8_t *pui8RegData);
extern uint32_t I2CReadRegMultiByte (uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr,uint8_t *pui8RegData,uint32_t ui32ReadCount);

#endif /* I2C_I2C_INIT_H_ */



