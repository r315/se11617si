#include <lpc2106.h>
#include <spi.h>

/**
*	default init 8-bit transfer
*   master, mode 3, clk = PCLK/4
**/
void SPI_Init(void){

	SC->PCONP &= ~(SSP0_ON | SPI0_ON);	

	SPI0->SPCR = SPI0_MSTR | SPI0_CPOL | SPI0_CPHA;
	SPI0->SPCCR = 4;	

	SC->PCONP |= SPI0_ON;
}

uint32_t SPI_Send(uint32_t data){
	SPI0->SPDR = data;
	while(!(SPI0->SPSR & SPI0_SPIF));
return SPI->SPDR;
}	
