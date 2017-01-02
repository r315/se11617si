#ifndef _save_h_
#define _save_h_

int saveData(void *data, int dataSize);
int restoreData(void *data, int dataSize);

#ifndef _EMU_
#define SAVE_BLOCK (uint32_t)((FLASH_LAST_SECTOR - 2) * FLASH_SECTOR_SIZE)
#else
static uint8_t SAVE_BLOCK[1024];
#endif


#endif
