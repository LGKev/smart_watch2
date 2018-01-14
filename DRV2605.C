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
    // the address of the device is
    EUSCI_B3 -> I2CSA = DRV2605_ADDRESS01; //not defined

    I2C_B3_init();

    EUSCI_B3->TXBUF = 0xAA; //get out of stand by?
}
