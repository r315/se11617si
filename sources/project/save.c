#include <string.h>
#include <stdint.h>
#include <flash.h>
#include "save.h"


int saveData(void *data, int dataSize){    
    FLASH_WriteData(SAVE_BLOCK, data, dataSize);
    return FLASH_VerifyData(SAVE_BLOCK, data, dataSize); 
}

int restoreData(void *data, int dataSize){
    memcpy(data, SAVE_BLOCK, dataSize);
    return CMD_SUCESS;
}
