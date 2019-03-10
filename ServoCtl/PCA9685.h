/*
 * PCA9685.h
 *
 *  Created on: 2018Äê9ÔÂ27ÈÕ
 *      Author: admin
 */

#ifndef SERVOCTL_PCA9685_H_
#define SERVOCTL_PCA9685_H_

/***************************/
#define PCA9685_I2C_ADD I2C0_BASE
#define PCA9685_ADD 0x40

/***************************/

#define MODE1 0x00
#define MODE2 0x01

#define SUBADR1 0x02
#define SUBADR2 0x03
#define SUBADR3 0x04

#define ALLCALLADR 0x05

#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09


#define ALL_LED_ON_L 0xFA
#define ALL_LED_ON_H 0xFB
#define ALL_LED_OFF_L 0xFC
#define ALL_LED_OFF_H 0xFD
#define PRE_SCALE 0xFE
#define TestMode 0xFF

#endif /* SERVOCTL_PCA9685_H_ */
