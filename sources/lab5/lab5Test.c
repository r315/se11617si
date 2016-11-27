#include <stdio.h>
#include <spi.h>
#include <led.h>
#include <lcd.h>
#include <timer.h>
#include <rtc.h>
#include <button.h>

#define TIME_FORMAT (2<<8) | 10  // representa em base decimal com um zero a esquerda 

int main(int argc, char *argv[]){
struct tm rtc;
	rtc.tm_sec = 50;
	rtc.tm_min = 25;
	rtc.tm_hour = 01;
	rtc.tm_mday = 10;
	rtc.tm_mon = 11;
	rtc.tm_year = 2016;
	rtc.tm_wday = 0;
   
    TIMER0_Init(MS_IN_1S);	

  	LED_Init(LED, LED_OFF);

  	BUTTON_Init();

  	RTC_Init(&rtc);

	SPI_Init(1000, SPI_8BIT); // lcd must be initialyze with low speed and 8bit transfers

	LCD_Init();

	SPI_Init(SPI_MAX_FREQ, SPI_16BIT);

	LCD_Clear(BLUE);

	LCD_SetColors(RED,BLUE);

	while(1){
		RTC_GetValue(&rtc);
		LCD_Goto(0,0);
		LCD_WriteInt(rtc.tm_hour,TIME_FORMAT);
		LCD_WriteChar(':');
		LCD_WriteInt(rtc.tm_min,TIME_FORMAT);
		LCD_WriteChar(':');
		LCD_WriteInt(rtc.tm_sec,TIME_FORMAT);
	}
	return 0;
}
 
