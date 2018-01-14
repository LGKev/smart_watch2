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
     EUSCI_B3->BRW = 0X0; //pre scaler for clock, might need this if the speed of the driver is limited
     //TODO: come back to this looking for the i2c change of transmit receive
     I2C_B3_PORT_config();
     EUSCI_B3->CTLW0 &= ~UCSWRST; //clear

//     EUSCI_B3->IFG = 0; //clear any flags
     EUSCI_B3->IE |= UCNACKIE | UCCLTOIE | UCRXIE0| UCTXIE0; //nack recieved, clock low time out, RX0
     NVIC_EnableIRQ(EUSCIB3_IRQn);
}



void set_Mode(uint8_t _mode){
    if(_mode == 1){
        EUSCI_B3->CTLW0 |= UCTR;
    }
    if(_mode ==0){
        EUSCI_B3->CTLW0 &= ~UCTR;
    }
}

/*
 *  Master talk to slave send data:
 *      1) master sends START condition and the slave's address
 *      2)master sends data to the slave
 *      3) master sends STOP conidition
 *
 *
 *          More Details:
 *          1) master sends address
 *          2) start condition triggered
 *          3) send write command
 *          4) send memory address
 *          5) send data with for loop
 *          6) send stop command.
 * */


void start_Transmission(uint8_t  _address){

//24.3.4.2.1 I2C, master transmitter mode
UCB3I2CSA = _address;
set_Mode(1);
EUSCI_B3->CTLW0 |= UCTXSTT;
}

void send_Data_TX(uint8_t _slave_Address, uint8_t * _data,  uint8_t _length){
    start_Transmission(_slave_Address);

  //  while(EUSCI_B3->STATW & UCBBUSY);
        //not busy
    uint8_t index;
    for(index = 0; index < _length;  index++){
        EUSCI_B3->TXBUF = _data[index];
    }
    //:TODO: this is where a stop bit could be generated

    stop_Transmission(_slave_Address);
}

void stop_Transmission(uint8_t _address){
    EUSCI_B3->CTLW0 |= UCTXSTP; //send stop command;
}

/* ================================================================================================================*/
/* ================================================================================================================*/
/* ================================                          I2C ISR Handler                           =========================================*/
/* ================================================================================================================*/
/* ================================================================================================================*/
void EUSCIB3_IRQHandler(){
    if(UCB3IFG & UCTXIFG){
        UCB3IFG &=~UCTXIFG;

//        UCB1CTLW0 |= UCTXSTP;
    }

    if(UCB3IFG & UCNACKIFG){
              UCB3IFG &=~UCNACKIFG;


              //start command again!
             EUSCI_B3->CTLW0 |= UCTXSTT;
          }


}
