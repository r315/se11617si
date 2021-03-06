#include <clock.h>

static __pclkval = 0;
static __cclkval = 0;

uint32_t CLOCK_GetPCLK(void){
uint8_t apbdiv_val;

    do{
        apbdiv_val = (SC->APBDIV & 3);        //see errata for "Incorrect read of VPBDIV"
    }while( (SC->APBDIV & 3) != apbdiv_val);

	if(!__pclkval)
	   switch(apbdiv_val){
	      default:
	      case 0: __pclkval = CLOCK_GetCCLK() / 4; break;
	      case 1: __pclkval = CLOCK_GetCCLK(); break;
	      case 2: __pclkval = CLOCK_GetCCLK() / 2; break;
    }
	return __pclkval;
}

uint32_t CLOCK_GetCCLK(void){
    if(!__cclkval)
        __cclkval = XTAL;
	return __cclkval;
}

void CLOCK_PllInit(uint8_t msel, uint8_t psel){
	SC->PLLCON = 1; //enable pll
	SC->PLLCFG = (psel<<5) | msel; 
	SC->PLLFEED = 0xAA;		//write PLLCON sequence
	SC->PLLFEED = 0x55;		//
	while(!(SC->PLLSTAT & (1<<10))); //wait for stabilization

	SC->PLLCON = 3; //connect pll to cclk
	SC->PLLFEED = 0xAA;
	SC->PLLFEED = 0x55;
    __cclkval = (msel+1) * XTAL;
}

