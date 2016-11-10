#include <time.h>
#include <rtc.h>
#include <led.h>

int main(void){
struct tm startime;
uint32_t state = LED_OFF;

	startime.tm_sec = 0;
	startime.tm_min = 0;
	startime.tm_hour = 20;
	startime.tm_mday = 10;
	startime.tm_mon = 11;
	startime.tm_year = 2016;
	startime.tm_wday = 0;

	RTC_Init(&startime);
	startime.tm_sec += 2;
	RTC_SetAlarmValue(&startime);
	
	RTC_ActivateAlarm(1); //seconds alarm

	LED_Init(LED,state);

	while(1){
		while(!RTC_HasAlarms());
		RTC_GetAlarmValue(&startime);
		startime.tm_sec += 2;
		RTC_SetAlarmValue(&startime);
		LED_SetState(state);
		state ^= 1;		
	}

return 0;
}
