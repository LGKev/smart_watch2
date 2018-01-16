#include "DRV2605.h"
#include "msp.h"
#include "I2C.h"
/*
 * DRV2605.C
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 */


 void DRV2605_PORT_config(){
     /* Enable: P7.5
      * PWM: P7.6
      * */
     P7SEL0 &= ~(BIT5 | BIT6);
     P7SEL1 &= ~(BIT5 | BIT6);

     P7DIR |= BIT5 | BIT6;
     P7OUT &= ~( BIT6); //PWM low
     P7OUT |= BIT5; //enable high.
 }

 void I2C_B3_PORT_config(){
  //    P6SEL0 |= BIT6 | BIT7; //Primary mode needs to be 1
   //   P6SEL1 &= ~( BIT6|BIT7); //needs to be  0
      //OR IS IT SECONDARY MODE!?
 //ITS SECONDARY MODE!!! ALWAY SREAD THE DATA SHEET
      P6SEL1 |= BIT6 | BIT7; //Primary mode needs to be 1
      P6SEL0 &= ~( BIT6|BIT7); //needs to be  0

      P6DIR &= ~(BIT6|BIT7);
      P6REN |= (BIT6|BIT7);
      P6OUT |= (BIT6|BIT7);
  }


/* init sequence from data sheet
 *  *     1) wait 250 uS before commands can be sent
 *     2) EN set high, during or after 250 wait
 *     3) write the mode register at address 0x01 to the value 0x00 to remove the device from standby
 *     4) perform auto calibration procedure
 *     5) using embedded ROM library (woo!), write the selection library address 0x03 to select a library
 *     6) default is closed loop bidirecitonal mode?!?!. control 1 0x01B, control 2, 0x1C, control 3 is 0x1D, open loop is recommended
 *              for the ERM mode but i don't have a rotating mass? I  have a linear resonant actuator. LRA
 *              7) put device in standby mode, or EN is low
 * */
void DRV2605_init(){
    //ENABLE DEVICE
    DRV2605_PORT_config();

    // the address of the device is
    EUSCI_B3 -> I2CSA = DRV2605_ADDRESS01_WRITE;  //default: 0x5A

    I2C_B3_init();

    DRV2605_Enable();


    //TODO need to do the calibration here.

}

void DRV2605_Enable(){
    P7OUT |= BIT5;
}
void DRV2605_Disable(){
    P7OUT &= ~BIT5;
}
