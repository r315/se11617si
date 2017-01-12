/**
* @file		clock.h
* @brief	Contains API header for returning the current CCLK and PCLK, also alows initializations of PLL.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/
#ifndef _clock_h_
#define _clock_h_

#include <lpc2106.h>

#define XTAL    14745600

uint32_t getPclk(void);
uint32_t getCclk(void);
void PLL_Init(void);

#endif
