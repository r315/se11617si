/**
* @file		flash.h
* @brief	Contains the Flash API header.
*     		
* @version	1.0
* @date		26 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _flash_h_
#define _flash_h_

#include <stdint.h>
#include <lpc2106.h>

/** 
* @brief Apaga o conteúdo de um sector, ou de múltiplos sectores, da FLASH. Para apagar
*        apenas um sector, deve usar-se o mesmo número de sector para os dois parâmetros.
**/
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector);

/**
* @brief Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes, no
*        endereço da FLASH referenciado por dstAddr. Pressupõe que os sectores envolvidos na
*        operação de escrita foram apagados previamente e que size não excede 4kB.
**/
unsigned int FLASH_WriteBlock( void *dstAddr, void *srcAddr, unsigned int size);

/**
* @brief Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes, no
*        endereço da FLASH referenciado por dstAddr.
**/
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);

/**
* @brief Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size
*        bytes, com o conteúdo do bloco de dados referenciado por dstAddr.
**/
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);

#endif
