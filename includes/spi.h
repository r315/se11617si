#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>

#define SPI0_ON (1<<8)
#define SSP0_ON (1<<21)

/* Control bits */
#define SPI0_EN_NBITS (1<<2)	//transfered bits selected by bits 11:8
#define SPI0_CPHA	  (1<<3)
#define SPI0_CPOL	  (1<<4)
#define SPI0_MSTR     (1<<5)	//Master mode
#define SPI0_LSBF	  (1<<6)
#define SPI0_SPIE     (1<<7)
#define SPI0_8BITS	  (8<<8)
#define SPI0_9BITS	  (9<<8)
#define SPI0_16BITS	  (0<<8)

/* status register bits */
#define SPI0_SPIF	  (1<<7)

#define SPI0_SCK (1<<4)
#define SPI0_MOSI (1<<6)
#define SPI0_MISO (1<<5)
#define SPI0_SSEL  (1<<7)

void SPI_Init(void);

uint32_t SPI_Send(uint32_t data);


#endif
