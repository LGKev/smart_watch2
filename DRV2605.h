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

#define DRV2605_ADDRESS01 0xFF //undefined!!!!

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
 *     6) default is closed loop bidirecitonal mode?!?!. control 1 0x01B, control 2, 0x1C, control 3 is 0x1D, open loop is recommended
 *              for the ERM mode but i don't have a rotating mass? I  have a linear resonant actuator. LRA
 *              7) put device in standby mode, or EN is low
 *
 *              note there is not a slave address
 * */
void DRV2605_init(void);

//TODO: do all the defines for the memory locations., finish the init of the driver.

/*
 * @brief: calibrates the LRA with the driver. using the data sheet recommended sequence:
 *          1) apply power and EN = HIGH (p7.5);
 *          2) write value: 0x07 to the register @0x01; moves out of STANDBY and places bits into the MOD[2:0] register (3 bits)
 *          3)s
 *
 * */
void DRV_Auto_Calibrate(void);

#endif /* DRV2605_H_ */
