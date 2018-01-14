#include "msp.h"


/*


 * I2C.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 */

#ifndef I2C_H_
#define I2C_H_

/*@breif: configures the i2c peripheral B3 for use with the Haptic Motor Driver DRV2605
 */
void I2C_B3_init(void);

/*
    @name: start_Transmission
    @brief: Writes _address to UCBIi2cA field. Sets master into TX mode and sets UCTXSTT start BIT
    @input: The address of the slave device
 */
void start_Transmission(uint8_t _address);


/* @name: stop_Transmission
 * @brief: Sets the UCTXSTP bit to trigger stop
   @input: Address of the slave in Hex
 */
void stop_Transmission(uint8_t _address);


/*  @name: write_Command
 *  @brief: Sequence of events required to write to the i2c BUS: Is this just as simple as looping over TX BUFFer?
 *  @inputs, command [hex]
 *      */
void wirte_Command(uint8_t );


void send_Data_TX(uint8_t _slave_Address, uint8_t * _data, uint8_t length);



//1 is transmit 0 is rx
void set_Mode(uint8_t _mode);


#endif /* I2C_H_ */
