#include <lpc2106.h>
#include <spi.h>
#include <gpio.h>
#include <clock.h>

/**
*	default init 8-bit transfer
*   master, mode 3, clk = PCLK/16
*   Note default pclk = cclk/4
**/
void SPI_Init(int frequency, int bitData){
int spccr;	

	SC->PCONP |= SPI0_ON;
	PINCON->PINSEL0 = SPI0_PINS;
	SPI0->SPCR = SPI0_MSTR | SPI0_CPOL | SPI0_CPHA;
	
	spccr = getPclk() / frequency;

	if(spccr < SPI_MAX_CLK)
		spccr = SPI_MAX_CLK;
		
	SPI0->SPCCR = spccr & 0xFE;	// must be an even number
}

uint16_t SPI_Send(uint16_t data){
	SPI0->SPDR = data;
	while(!(SPI0->SPSR & SPI0_SPIF));
return SPI0->SPDR;
}

void SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int lenght){
	while(lenght--){
		*rxBuffer++ = SPI_Send(*txBuffer++);
	}
}

void SPI_BeginTransfer(int csBitId){
	GPIO_Clr(csBitId);
}

void SPI_EndTransfer(int csBitId){
	GPIO_Set(csBitId);
}




