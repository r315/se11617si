#include <spi.h>
#include <led.h>

#define DEV_CS (1<<3)

void delayMs(uint32_t ms){
volatile int dlms;

	while(ms--){
		dlms = 14745;
		while(dlms--);
	}
}																			 

int main(int argc, char *argv[]){

	SPI_Init(16, 8);
	LED_Init(LED, LED_OFF);
	
	while(1){ 
		LED_SetState(LED_OFF);
		SPI_Send('U');		
		LED_SetState(LED_ON);
		delayMs(200);		
	}
	return 0;
}
 
