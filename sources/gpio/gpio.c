#include <lpc2106.h>
#include <gpio.h>


void GPIO_Init(uint8_t bit, uint8_t dir, uint8_t state){
	GPIO0->DIR &= ~(1<< bit);
	GPIO0->DIR |= (dir<< bit);
	GPIO_SetPin(bit, state);
}

void GPIO_SetPin(uint8_t bit, uint8_t state){
	if(state)
		GPIO0->SET = (1<<bit);
	else
		GPIO0->CLR = (1<<bit);
}

uint8_t GPIO_GetPin(uint8_t bit){
	return (GPIO0->PIN & (1<<bit)) == 1? 1 : 0;
}
