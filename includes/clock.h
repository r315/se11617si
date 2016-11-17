#ifndef _clock_h_
#define _clock_h_

#include <lpc2106.h>

#define XTAL    14745600
#define CCLK	XTAL
#define PCLK	(CCLK / 4) //default

uint32_t getPclk(void);
uint32_t getCclk(void);

#endif
