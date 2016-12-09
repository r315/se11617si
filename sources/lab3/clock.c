#include <clock.h>

static __pclkval = 0;
static __cclkval = 0;

uint32_t getPclk(void){
	if(!__pclkval)
	   switch(SC->APBDIV & 3){
	      default:
	      case 0: __pclkval = getCclk() / 4; break;
	      case 1: __pclkval = getCclk(); break;
	      case 2: __pclkval = getCclk() / 2; break;
   		}
	return __pclkval;
}

uint32_t getCclk(void){
    if(!__cclkval)
        __cclkval = XTAL;
	return __cclkval;
}

//TODO fix timer due to cclk change
void PLL_Init(void){
#define MSEL 4 // MSEL and PSEL for CCLK = 73.728Mhz
#define PSEL 1
	SC->PLLCON = 1; //enable pll
	SC->PLLCFG = (PSEL<<5) | MSEL; 
	SC->PLLFEED = 0xAA;		//write PLLCON sequence
	SC->PLLFEED = 0x55;		//
	while(!(SC->PLLSTAT & (1<<10))); //wait for stabilization

	SC->PLLCON = 3; //connect pll to cclk
	SC->PLLFEED = 0xAA;
	SC->PLLFEED = 0x55;
    __cclkval = 73728000;
}

