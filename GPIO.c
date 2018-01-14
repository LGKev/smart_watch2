#include "msp.h"
#include "GPIO.h"

/*


 * GPIO.c
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 */

/*@brief: this function will initialize three GPIO as inputs, refer to the schematic if confused.
 * Button 1: P9.2   - (in the schematic this is S2)
 * Button 2  P9.0   - (in the schematic this is S3)
 * Button 3: P2.7   - (in the schematic this is S4)
 * */
 void button_init(void){
     P6SEL0 &= ~(BIT2 | BIT0);
     P6SEL1 &= ~(BIT2 | BIT0);
     P2SEL0 &= ~BIT7;
     P2SEL1 &= ~BIT7;

     P6DIR &= ~(BIT2 | BIT0); //input
     P2DIR &= ~BIT7; //input
     //pullup,
     P6REN |= BIT2 | BIT0;
     P2REN |= BIT7;
// transition is going to be on the rising edge.
     P6IES &= ~(BIT2 | BIT0);
     P2IES &= ~BIT7;
     //pull up
     P6OUT |= BIT2 | BIT0;
     P2OUT |= BIT7;
     //clear flags
     P6IFG = 0;
     P2IFG = 0;
     //enable interrupts
     P6IE |= BIT2 | BIT0;
     P2IE |= BIT7;

//enable interrupts on the ports
         NVIC_EnableIRQ(PORT6_IRQn); //6.2 is button 1, and 6.0 is button 2
         NVIC_EnableIRQ(PORT2_IRQn); //2.7 button 3, remember button 1 is related to the switch location not the schematics
 }
 /*
 *  @brief: initialize the gpio pin for the blue heartbeat
 *  P9.3
 * */
 void heartbeat_led_init(){
    //Heartbeat LED P9.3
     P9SEL0 &= ~BIT3;
     P9SEL1 &= ~BIT3;
     P9DIR |= BIT3;
     P9OUT |= BIT3;
 }
 /*
  *  INTERRUPT HANDLERS FOR THE BUTTONS BELOW
  *     CLEAR THE APPROPRIATE FLAGS.
  * */

 //interrupt for button 2
 PORT6_IRQHandler(){
     if(P6IFG & BIT2){
         //button 1 fired
         P6->IFG &= ~BIT2; //clear that flag
     }
     if(P6IFG & BIT0){
         //button 2 fired
         P6->IFG &= ~BIT0; //clear that flag
     }
 }

 PORT2_IRQHandler(){
     if(P2IFG & BIT7){
         //button 1 fired
         P2->IFG &= ~BIT7; //clear that flag
     }
 }
