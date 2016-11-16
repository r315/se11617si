/**
* @file		spi.h
* @brief	Contains the spi API header.
*     		
* @version	1.0
* @date		5 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

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

/* pincon function select */
/*Remark: LPC2104/05/06 and LPC2104/05/06/00 configured to operate as a SPI master MUST
select SSEL functionality on P0.7 and have HIGH level on this pin in order to act as a master.*/
#define SPI0_PINS (0x55<<8)

#define SPI_MAX_CLK 8		//min pckl divider
/**
* @brief Faz a iniciação do controlador, configurando os pinos, o ritmo de envio e o
*        numero de bits de dados.
*/
void SPI_Init(int clk, int bitData);

/**
* @brief Coloca ativo o chip select do dispositivo slave
*/
void SPI_BeginTransfer(int csBitId);

/**
* @brief Coloca desativo o chip select do dispositivo slave
**/
void SPI_EndTransfer(int csBitId);

/**
* @brief Realiza uma transferencia. 
**/
void SPI_Transfer(unsigned short *txBuffer, unsigned short arxBuffer, int lenght);


/**
* @brief initiates and 8bit data transfer
*		 rev 00 only suports 8bit
**/
uint32_t SPI_Send(uint16_t data);

#endif
