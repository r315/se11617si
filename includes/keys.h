/**
* @file		keys.h
* @brief	common functions for keys access
* @version	1.0
* @date		30 Out. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

typedef struct{
	uint32_t cur;
	uint32_t last;
	uint32_t hold;
	uint32_t count;
}B_STATE;

#define B_L       (1<<16)
#define B_R       (1<<15)
#define B_F       (1<<14)
#define B_S       (1<<13)
#define B_MASK    (B_L | B_R | B_F | B_S)
#define B_EMPTY   0
#define B_HOLD_TIME 2000   //2 seconds

#define ON 1
#define OFF 0

/**
 * @brief	Read Keys. 
 * @return	key(s) read code or B_EMPTY (0)
 */
uint32_t readKeys(void);

uint32_t readLastKey(void);

#endif

