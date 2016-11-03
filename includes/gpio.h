/**
* @file		gpio.h
* @brief	common functions for io port access
* @version	1.0
* @date		30 Out. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include <lpc2106.h>

#define GPIO_Set(x) GPIO0->SET = x
#define GPIO_Clr(x) GPIO0->CLR = x
#define GPIO_Read() GPIO0->PIN
#define GPIO_Write(x) GPIO0->PIN = x
#define GPIO_OUTPUT	1
#define GPIO_INPUT	0

#define P04_SCK  (1<<8)
#define P05_MISO (1<<10)
#define P06_MOSI (1<<12)



/**
 * @brief	Initialyze Port indicating output pins ans their state. 
 *			bits as 1 are configured as outputs
 */
void GPIO_Init(uint32_t output, uint32_t state);
void GPIO_SetPin(uint8_t bit_number, uint8_t state);
void GPIO_ConfigPin(uint32_t bit_number, uint32_t dir); //configure pin using his bit number
void GPIO_ConfigPinMask(uint32_t mask, uint32_t dir);	//configures pin using his mask

#endif

