/*
 * GPIO.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 *
 *		@brief: these are the functions to configure various gpio, such as the buttons hearbeat led.
 *		the buttons will take the convention of button 1 being top right button 2 is the bottom right and then button 3 is the bottom left locations.
 *		oriented such that the JTAG is to the top of the board.
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

 void button_init(void); //initialize the three buttons

 void heartbeat_led_init(void); //initialize the blue led indicating system is running.

 /* @brief: this configures the pins 6.6 and 6.7 to be the "primary" mode so that I2C can be used.
  * This will be called from I2C.c file to initiailze the ports.
  * */
 void I2C_B3_PORT_config(void);
/*
 * @brief: this configures the pins 7.5 and 7.6 for the ENABLE AND PWM of the motor driver
 *          both are configured as outputs?
 *          TODO confirm what the configuration for pwm is.
 * */
 void DRV2605_PORT_config();



#endif /* GPIO_H_ */
