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

/**
 * @brief	Initialyze Port indicating output pins ans their state. 
 *			bits as 1 are configured as outputs
 */
void GPIO_Init(uint32_t output, uint32_t state);

/**
 * @brief	Read Port. 
 * @return	status of port 0 indicating the state of all 32bit.
 */
uint32_t GPIO_Read(void);

void GPIO_Write(uint32_t value);

void GPIO_Set(uint32_t value);

void GPIO_Clr(uint32_t value);

void GPIO_Pin(uint8_t pin_number, uint8_t state);



#endif

