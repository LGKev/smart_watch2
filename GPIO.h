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






#endif /* GPIO_H_ */
