#include <lpc2106.h>
#include <gpio.h>



void GPIO_Init(uint32_t output, uint32_t state){
	GPIO0->DIR = output;   /* Legacy version :( */	
	GPIO0->PIN = state;
}

uint32_t GPIO_Read(void){
	return GPIO0->PIN;
}

void GPIO_Write(uint32_t value){
	GPIO0->PIN = value;
}

void GPIO_Set(uint32_t value){
	GPIO0->SET = value;
}

void GPIO_Clr(uint32_t value){
	GPIO0->CLR = value;
}

void GPIO_Pin(uint8_t pin_number, uint8_t state){
	if(state)
		GPIO0->SET = (1<<pin_number);
	else
		GPIO0->CLR = (1<<pin_number);
}

 
