#include <timer.h>
#include <led.h>
#include <button.h>


void LED_Blink(uint32_t ms){
      LED_SetState(LED_ON);
      TIMER0_DelayMs(ms);
      LED_SetState(LED_OFF);
}


int main (void){

	TIMER0_Init(MS_IN_1S);
	LED_Init(LED,LED_OFF);
	BUTTON_Init(BUTTON_MASK);

	while(1){			
		switch(BUTTON_Read()){
			case BUTTON_L:
				LED_Blink(500);
		  		break;
			case BUTTON_R:
				LED_Blink(1000);
		  		break;
			case BUTTON_F:
				LED_Blink(1500);
		  		break;
			case BUTTON_S:
				LED_Blink(2000);
		  		break;		         
			case BUTTON_L | BUTTON_R:
				if(BUTTON_GetButtonsEvents() != BUTTON_HOLD)
					break;
				LED_Blink(30);
				TIMER0_DelayMs(70);
				LED_Blink(30);
				break;		
         }
	}
	return 0;	
}
