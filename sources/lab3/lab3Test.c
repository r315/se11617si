#include <timer.h>
#include <led.h>
#include <button.h>

int main (void){
uint32_t lasttime;

	TIMER0_Init(1000);
	LED_Init(LED,LED_ON);
	lasttime = TIMER0_GetValue();
	BUTTON_Init(1<<11);

	while(1){		
		/*if(TIMER0_Elapse(lasttime) >= 1){
			LED_SetState(LED_GetState() ^ 1);
			lasttime = TIMER0_GetValue();
		}*/

		if(BUTTON_GetButtonsEvents() == BUTTON_HOLD)
			LED_SetState(LED_ON);
		else
			LED_SetState(LED_OFF);


	}
	return 0;	
}
