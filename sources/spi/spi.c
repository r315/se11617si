#include <lpc2106.h>
#include <spi.h>

/**
*	default init 8-bit transfer
*   master, mode 3, clk = PCLK/16
*   Note default pclk = cclk/4
**/
void SPI_Init(uint8_t clk){	
	SC->PCONP |= SPI0_ON;
	PINCON->PINSEL0 = SPI0_PINS;
	SPI0->SPCR = SPI0_EN_NBITS | SPI0_MSTR | SPI0_CPOL | SPI0_CPHA;
	if(clk < SPCCR_MIN)
		clk = SPCCR_MIN;
	SPI0->SPCCR = clk;	
}

uint32_t SPI_Send(uint16_t data){
	SPI0->SPDR = data;
	while(!(SPI0->SPSR & SPI0_SPIF));
return SPI0->SPDR;
}

void SPI_SetBits(uint8_t nbits){	
	SPI0->SPCR &= (~0x0F << 8); 
	SPI0->SPCR |= (nbits << 8);
}
	
