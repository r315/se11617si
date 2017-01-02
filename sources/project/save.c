#include <stdint.h>
#include <flash.h>
#include "save.h"

int saveData(void *data, int dataSize){
    #ifndef _EMU_
    return FLASH_WriteData(SAVE_BLOCK,data,dataSize);
    #else
    uint8_t *dst = SAVE_BLOCK;
    while(dataSize--)
        *dst++ = *((uint8_t*)data++);                
    return CMD_SUCESS;
    #endif
}

int restoreData(void *data, int dataSize){
uint8_t *src = SAVE_BLOCK;
    while(dataSize--)
        *((uint8_t*)data++) = *src++;        
    return CMD_SUCESS;
}
