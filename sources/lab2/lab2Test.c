#include <led.h>

#define WAIT_200MS 200 //2,5Hz => T=400ms

void delay(int time);

int main(int argc, char *argv[]){
int state = LED_ON;    
    
	LED_Init(LED, state);
    
	while(1){
		LED_SetState(state);
		delay(WAIT_200MS);
		state ^= 0x01;
	}
	return 0;
}
