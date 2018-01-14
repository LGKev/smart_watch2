#include "msp.h"
#include "I2C.h"
#include "GPIO.h"
/*
 * I2C.C
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 *		@brief this is essentially just for the haptic motor driver DRV2605
 */

/*@brief: this is for the I2C peripheral B3, the pins are 80 and 81 of the QFN package
 *          SDA is p6.6 and SCL is p6.7
 *          //steps to initialize from the datasheet
 *          1) set UCSWRST
 *          2) init eUSCI_B register while USCWRST = 1
 *          3) configure the ports: 6.6 and 6.7
 *          4) clear the USWRST ie = 0
 *          5) inable intererupts, probably clear interrupts before this
 * */
void I2C_B3_init(){
    EUSCI_B3->CTLW0 |= UCSWRST; //set

     EUSCI_B3->CTLW0 &= ~(UCSLA10 | UCMM); //7 bit slave address, single master on the b3 i2c lines
     EUSCI_B3->CTLW0 |= UCMST | UCMODE_3 | UCSYNC; //msp is the master, i2c mode (mode 3), synchronous
     EUSCI_B3->CTLW0 |=UCSSEL__SMCLK; //we'll use the system clock
     //we are transmitting .. but wait what about the drv closed loop feedback? i think it changes
     //TODO: come back to this looking for the i2c change of transmit receive
     EUSCI_B3->CTLW0 |= UCTR | UCTXSTT; //transmitter mode (might change), finally generate the start condition

     EUSCI_B3->BRW = 1; //pre scaler for clock, might need this if the speed of the driver is limited

     EUSCI_B3->CTLW0 &= ~UCSWRST; //clear

     I2C_B3_PORT_config();
     EUSCI_B3->IFG = 0; //clear any flags
     EUSCI_B3->IE |= UCNACKIE | UCCLTOIE | UCRXIE0; //nack recieved, clock low time out, RX0
}

