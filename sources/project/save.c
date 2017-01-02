#include <stdint.h>
#include <flash.h>
#include "save.h"

int saveData(void *data, int dataSize){    
    return FLASH_WriteData(SAVE_BLOCK,data,dataSize);    
}

int restoreData(void *data, int dataSize){
    memcpy(data,SAVE_BLOCK, dataSize);
    return CMD_SUCESS;
}
