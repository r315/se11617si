#include <lpc2106.h>
#include <gpio.h>


void GPIO_Init(uint32_t output, uint32_t state){
	GPIO0->DIR = output;   /* Legacy version :( */	
	GPIO0->PIN = state;
}

void GPIO_ConfigPin(uint32_t pin_number, uint32_t dir){
	GPIO0->DIR &= ~(1<<pin_number);
	GPIO0->DIR |= (1<<pin_number);
}

void GPIO_SetPin(uint8_t pin_number, uint8_t state){
	if(state)
		GPIO0->SET = (1<<pin_number);
	else
		GPIO0->CLR = (1<<pin_number);
}

