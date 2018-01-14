#include "msp.h"
/*

 * DRV2605.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 */

#ifndef DRV2605_H_
#define DRV2605_H_

#define

/* @brief: this will initialize the motor driver
 * @depends: on the i2c.c and gpio.c files
 *      the i2c.c file will initialize the  i2c peripheral
 *      the gpio.c file will inititalize the ports for the i2c peripheral as well as setting up the motor PWM, ENABLE pins
 *          motor_pwm   =   p7.6
 *          motor_enable = pin7.5
 *
 *              from data sheet:
 *              init procedure:
 *     1) wait 250 uS before commands can be sent
 *     2) EN set high, during or after 250 wait
 *     3) write the mode register at address 0x01 to the value 0x00 to remove the device from standby
 *     4) perform auto calibration procedure
 *     5) using embedded ROM library (woo!), write the selection library address 0x03 to select a library
 *     6) default is closed loop bidirecitonal mode?!?!. control 1 0x01B, control 2, 0x1C, control 3 is 0x1D
 * */
void DRV2605_init(void);

#endif /* DRV2605_H_ */
