#include <flash.h>


uint32_t command[5], result[3];

/**
*    this functions returns directly to caller, so no need to save context
**/
__attribute__ ((naked)) void iap_entry(uint32_t *cmd, uint32_t *res){    
    asm("ldr r2,[pc]");
    asm("bx  r2");
    asm(".word 0x7FFFFFF1");
}


unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector){

}


unsigned int FLASH_WriteBlock( void *dstAddr, void *srcAddr, unsigned int size){
}


unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size){
}


unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size){
}

