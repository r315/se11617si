#include <led.h>
#include <gpio.h>

#define ON 1
#define OFF 0

#define LED (1<<12)

#define WAIT_200MS 200 //2,5Hz => T=400ms

void delay(int time);

int main(int argc, char *argv[]){
int state = OFF;
	GPIO_Init(LED,0);

	while(1){
		GPIO_Write(state == 0 ? LED : 0);
		delay(WAIT_200MS);
		state ^= 0x01;
	}
	return 0;
}
