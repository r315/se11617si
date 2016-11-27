#include <flash.h>
#include <clock.h>


uint32_t __command[5], __result[3];

/**
* @brief call's IAP function in thumb mode.
* @param pointer to command an parameter table
* @param pointer to result table
**/
__attribute__ ((naked)) void iap_entry(uint32_t *command, uint32_t *result){    
    asm("ldr r2,[pc]");
    asm("bx  r2");
    asm(".word 0x7FFFFFF1");
}

/**
* @brief prepares sector(s) for errase or write
* @param start sector
* @param end sector
* @return CMD_SUCCESS, BUSY, INVALID_SECTOR
**/
uint32_t prepare_sector(uint32_t start, uint32_t end){
    __command[0] = FLASH_PREPARE_SECTOR;
    __command[1] = start;
    __command[2] = end;
    __command[3] = getCclk() / 1000;  //clock specified in Khz
    iap_entry(__command,__result);
    return __result[0];
}


unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector){
     if( prepare_sector(startSector,endSector) == CMD_SUCESS){
        __command[0] = FLASH_ERASE_SECTOR;
        __command[1] = startSector;
        __command[2] = endSector;
        __command[3] = getCclk() / 1000;
        iap_entry(__command,__result);
     }
    return __result[0];
}


unsigned int FLASH_WriteBlock( void *dstAddr, void *srcAddr, unsigned int size){
}


unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size){
}


unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size){
}

