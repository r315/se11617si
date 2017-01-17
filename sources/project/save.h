/**
* @file     save.h
* @brief    Contains API header save and restore data from flash memory
*
* @version  1.0
* @date     12 dec. 2016
* @author   Hugo Reis
**/
#ifndef _save_h_
#define _save_h_

int saveData(void *data, int dataSize);
int restoreData(void *data, int dataSize);

#ifndef _EMU_
#define SAVE_BLOCK (uint32_t)((FLASH_LAST_SECTOR - 2) * FLASH_SECTOR_SIZE)
#else
static uint8_t SAVE_BLOCK[0x2000];
#endif


#endif
