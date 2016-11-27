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

#define FLASH_BLOCK_SIZE 0x2000 //8k
#define FLASH_LAST_SECTOR 0x0F

#define FLASH_BOOT_BLOCK_BASE 0x7FFFE000

#define FLASH_PREPARE_SECTOR 50
#define FLASH_RAM_TO_FLASH   51
#define FLASH_ERASE_SECTOR   52

typedef enum {
    CMD_SUCESS = 0,
    INVALID_COMMAND,
    SRC_ADDR_ERROR,
    DST_ADDR_ERROR,
    SRC_ADDR_NOT_MAPPED,
    DST_ADDR_NOT_MAPPED,
    COUNT_ERROR,
    INVALID_SECTOR,
    SECTOR_NOT_BLANK,
    SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
    COMPARE_ERROR,
    BUSY
};

/** 
* @brief Apaga o conteúdo de um sector, ou de múltiplos sectores, da FLASH. Para apagar
*        apenas um sector, deve usar-se o mesmo número de sector para os dois parâmetros.
* @return CMD_SUCCESS,SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION, INVALID_SECTOR
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

