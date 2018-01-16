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

#define DRV2605_ADDRESS01 0x5A  //7 bit address.
#define DRV2605_ADDRESS01_WRITE 0xB4 //write wit a 0?
#define DRV2605_ADDRESS01_READ 0XB5
/*
 *  @brief: configures the ENABLE pin and the PWM pin
 *          ENABLE: p7.5
 *          PWM: P7.6
 *          Both are outputs.
 *         Authomattically sets the enable pin HIGH on exit.
 * */
void DRV2605_PORT_config(void);

/* @brief: this configures the pins 6.6 and 6.7 to be the "primary" mode so that I2C can be used.
 * This will be called from I2C.c file to initiailze the ports.
 * */
void I2C_B3_PORT_config(void);

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
 * * */
void DRV2605_init(void);


/*
 * @brief: Enables the motor driver by putting enable pin high.
 *              note: for the watch this is port 7.4
 * */
void DRV2605_Enable(void);

/*
 * @brief: Disables the motor driver by putting enable pin low.
 *              note: for the watch this is port 7.4
 *
 *               * */
void DRV2605_Disable(void);


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
