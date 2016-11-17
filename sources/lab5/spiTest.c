
#include <spi.h>
#include <led.h>
#include <lcd.h>
#include <timer.h>
#include <rtc.h>
#include <button.h>


int main(int argc, char *argv[]){
struct tm rtc;
	rtc.tm_sec = 0;
	rtc.tm_min = 0;
	rtc.tm_hour = 20;
	rtc.tm_mday = 10;
	rtc.tm_mon = 11;
	rtc.tm_year = 2016;
	rtc.tm_wday = 0;
   
   TIMER0_Init(MS_IN_1S);	
  	LED_Init(LED, LED_OFF);
  	BUTTON_Init();
  	RTC_Init(&rtc);
	SPI_Init(16, 8);
	LCD_Init();
	
	while(1){ 
		
	}
	return 0;
}
 
