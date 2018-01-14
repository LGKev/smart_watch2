#include "DRV2605.h"
#include "msp.h"
/*
 * DRV2605.C
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 */

void DRV2605_init(){
    // the address of the device is
    EUSCI_B3 -> I2CSA = DRV2605_ADDRESS01;
}
