#include <lpc2106.h>

#define ON 1
#define OFF 0

#define SPI_ON

#define SPI_EN (1<<2)
#define SPI_MSTR (1<<5)
#define SPI_SCK (1<<4)
#define SPI_MOSI (1<<6)
#define SPI_MISO (1<<5)
#define SPI_SSEL  (1<<7)

int main(int argc, char *argv[]){

	SC->PCONP_BITS.PCSSP = ON;
	SC->PCONP_BITS.PCSPI = OFF;
	
	PINCON->PINSEL0 = SPI_SCK | SPI_MOSI | SPI_MISO | SPI_SSEL;
	
	SPI0->SPCCR = 16; /* PCLK/16 */
	SPI0->SPCR = SPI_EN | SPI_MSTR;
	
	
	
	while(1){ 
		SPI0->SPDR = 'U';
	}
	return 0;
}
 