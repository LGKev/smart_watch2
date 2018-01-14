#include "msp.h"
#include "GPIO.h"
#include "RTC.h"


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


	__enable_interrupts();

	uint16_t delay;

	while(1){
	}


}
