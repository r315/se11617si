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

void SPI_Init(uint8_t clk){	
	SC->PCONP |= SPI0_ON;
	PINCON->PINSEL0 = SPI0_PINS;
	SPI0->SPCR = SPI0_MSTR | SPI0_CPOL | SPI0_CPHA;
	if(clk < SPCCR_MIN)
		clk = SPCCR_MIN;
	SPI0->SPCCR = clk;	
}

uint32_t SPI_Send(uint16_t data){
	SPI0->SPDR = data;
	while(!(SPI0->SPSR & SPI0_SPIF));
return SPI0->SPDR;
}
																			 

int main(int argc, char *argv[]){

	SPI_Init(16);
	LED_Init(LED, LED_OFF);
	
	while(1){ 
		LED_SetState(LED_OFF);
		SPI_Send('U');		
		LED_SetState(LED_ON);
		delayMs(200);		
	}
	return 0;
}
 
