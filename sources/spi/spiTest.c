#include <spi.h>
#include <gpio.h>

#define LCD_CS (1<<12)

void delayMs(uint32_t ms){
volatile int dlms;

	while(ms--){
		dlms = 14745;
		while(dlms--);
	}
}

void SPI_Init(void){

	SC->PCONP &= ~(SSP0_ON | SPI0_ON);	

	SPI0->SPCR = SPI0_MSTR | SPI0_CPOL | SPI0_CPHA;
	SPI0->SPCCR = 16;	

	SC->PCONP |= SPI0_ON;
}

uint32_t SPI_Send(uint32_t data){
	//if(SPI0->SPSR & SPI0_SPIF)
		SPI0->SPDR = data;
	while(!(SPI0->SPSR & SPI0_SPIF));
return SPI0->SPDR;
}	

int main(int argc, char *argv[]){

	GPIO_Init(LCD_CS,LCD_CS);
	SPI_Init();
	GPIO_ConfigPin(LCD_CS, GPIO_OUTPUT);
	
	while(1){ 
		GPIO_Clr(LCD_CS);
		SPI_Send('U');
		delayMs(500);
		GPIO_Set(LCD_CS);		
	}
	return 0;
}
 
