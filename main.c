#include "msp.h"
#include "GPIO.h"
#include "RTC.h"
#include "I2C.h"
#include "DRV2605.h"


/**
 * main.c
 *
 * Smart Watch V2 code base.
 * Peripherals involved: GPIO, I2C, SPI, UART, RTC
 * Devices Connected: BLE Serial, DRV Haptic motor driver, WS2812b, ePaper display, Barometer, BMA280 Accelerometer.
 *
 *
 *
 *
 * TODO: Get as many of the small things done as possible first. then do bigger stuff.
 *
 *  Lets get the RTC configured.
 *
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer



	RTC_init(0, 0, 0, 0, 0, 0, 0, 0); //will pass in time from compiler...? or from user... anyway it basically works.
	button_init(); //works
	heartbeat_led_init(); //works


	//lets get the motor driver working!
	I2C_B3_init();

	__enable_interrupts();

	uint8_t delay = 0;

	 DRV2605_init();

	while(1){
//	    send_Data_TX(0x01, delay, 1);
	  //  start_Transmission(0x5A);

start_Transmission(0x5A);
//stop_Transmission(0x5A);


	    for(delay = 0 ; delay<3000; delay++);
	}

	//TODO! set up the driver pin enable to be high, we need to do that first.
	//before we can communicate.
	//send_Data_TX(_slave_Address, _data, 1);

	while(1);

}
