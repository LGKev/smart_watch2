/*
 * RTC.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Kevin Kuwata
 *		
 */

#include "msp.h"


#ifndef RTC_H_
#define RTC_H_
/*============================================*/
/*============================================*/
/*=========       RTC Config Globals               ==========*/
/*============================================*/
volatile uint32_t second;
volatile uint8_t minute;
volatile uint8_t hour;
volatile uint8_t day_of_week;
volatile uint8_t day;
volatile uint8_t month;
volatile uint16_t year;
volatile uint8_t AM ;    //AM is 0, and PM is 1

/*
 *  @brief: this will initialize the RTC internal to the MSP.
 *  @inputs: expects to be given: month, day, year, time (hour, minute, seconds), and am/pm in Binary Coded Decimal.
 *      Example:
 *      TODO put an example in here.
 *  */
void RTC_init(uint8_t _month, uint8_t _day, uint16_t _year, uint8_t _weekday, uint8_t _hour, uint8_t minute, uint8_t _second, uint8_t _AM );

#endif /* RTC_H_ */
