#include "msp.h"
#include "RTC.h"

/*
 * RTC.c


 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 */

void RTC_init(uint8_t _month, uint8_t _day, uint16_t _year, uint8_t _weekday, uint8_t _hour, uint8_t minute, uint8_t second, uint8_t _AM ){

    RTC_C->CTL0 = RTC_C_KEY | RTC_C_CTL0_TEVIE | RTC_C_CTL0_RDYIE; //Real time clock key (for activation)
    RTC_C->CTL13 = RTC_C_CTL13_HOLD | //disable clock while adjusting settings
               RTC_C_CTL13_MODE | //set calendar mode
               RTC_C_CTL13_BCD ; //bcd mode

    RTC_C_BCD->TIM0= 0x0400;   //minutes, seconds
    RTC_C_BCD->TIM1=0x0604;  //day of week, hour

    RTC_C_BCD->DATE=0x0113;  //month, day
    RTC_C_BCD->YEAR=0x2018;  //year
    RTC_C->CTL13 &= ~RTC_C_CTL13_HOLD; //enable clock
    RTC_C->CTL0 &= ~(RTC_C_CTL0_KEY_MASK); //lock the registers


    NVIC_EnableIRQ(RTC_C_IRQn);

}


void RTC_C_IRQHandler(void)
{
    //occurs every 1 second
    if(RTC_C->CTL0 & RTCRDYIFG)
    {
        //BCD output registers

        //TIM0 is 16 bit seconds and minutes register
        second = RTC_C_BCD->TIM0;

        minute = (RTC_C_BCD->TIM0 >> RTC_C_TIM0_MIN_OFS);
        //TIM1 is 16 bit hour and day of week register
        hour = RTC_C_BCD->TIM1;
        day_of_week = (RTC_C_BCD->TIM1 >> RTC_C_TIM1_DOW_OFS);
        //DATE is 16 bit day and month register
        day = RTC_C_BCD->DATE;
        month = (RTC_C_BCD->DATE >> RTC_C_DATE_MON_OFS);
        //YEAR
        year = RTC_C_BCD->YEAR;

        // Unlock the RTC module and clear time event interrupt flag
        RTC_C->CTL0 = (RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK |  RTCRDYIFG)) | RTC_C_KEY;

        //RTC_C_CTL0_TEVIFG time event flag

        // Re-lock the RTC
        RTC_C->CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);

        //TOGGLE HEARTBEAT
            P9OUT ^= BIT3; // led
    }
//clear any flags TODO: this was a major bug the last time so be sure this isn't clearning too many flags.
    RTC_C->CTL0 = (RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK |  RTCRDYIFG | RTCOFIFG| RTCTEVIFG)) | RTC_C_KEY;
    RTC_C->CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);

}
