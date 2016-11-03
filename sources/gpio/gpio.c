#include <lpc2106.h>
#include <gpio.h>


void GPIO_Init(uint32_t output, uint32_t state){
	GPIO0->DIR = output;   /* Legacy version :( */	
	GPIO0->PIN = state;
}

void GPIO_ConfigPin(uint32_t bit_number, uint32_t dir){
	GPIO0->DIR &= ~(1<< bit_number);
	if(dir == GPIO_OUTPUT)
		GPIO0->DIR |= (1<< bit_number);
}

void GPIO_SetPin(uint8_t bit_number, uint8_t state){
	if(state)
		GPIO0->SET = (1<<bit_number);
	else
		GPIO0->CLR = (1<<bit_number);
}

void GPIO_ConfigPinMask(uint32_t mask, uint32_t dir){
	GPIO0->DIR &= ~(mask);
	if(dir)
		GPIO0->DIR |= (mask);
}
