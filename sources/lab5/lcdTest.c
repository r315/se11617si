#include <timer.h>
#include <button.h>
#include <display.h>
#include <spi.h>

//TODO fix timer due to cclk change
void PLL_Init(void){
#define MSEL 4
#define PSEL 1
	SC->PLLCON = 1; //enable pll
	SC->PLLCFG = (PSEL<<5) | MSEL; // 73.728Mhz
	SC->PLLFEED = 0xAA;		//write PLLCON sequence
	SC->PLLFEED = 0x55;		//
	while(!(SC->PLLSTAT & (1<<10))); //wait for stabilization

	SC->PLLCON = 3; //connect pll to cclk
	SC->PLLFEED = 0xAA;
	SC->PLLFEED = 0x55;	
}

	

int main(void){

	TIMER0_Init(MS_IN_1S);	

	BUTTON_Init();	
	
	SPI_Init(SPI_MAX_CLK);	

	LCD_Init();

	PLL_Init();

	LCD_OpenWrap(0,0,LCD_W,LCD_H);
	LCD_Fill(BLACK,LCD_SIZE);

	while(1){			
		switch(BUTTON_Read()){
			case BUTTON_L:
				LCD_Fill(RED,LCD_SIZE);				
		  		break;
			case BUTTON_R:
				LCD_Fill(GREEN,LCD_SIZE);	
		  		break;
			case BUTTON_F:
				LCD_Fill(BLUE,LCD_SIZE);	
		  		break;
			case BUTTON_S:
				LCD_Fill(WHITE,LCD_SIZE);	
		  		break;		         
			case BUTTON_L | BUTTON_R:
				if(BUTTON_GetButtonsEvents() != BUTTON_HOLD)
					break;
				LCD_Fill(BLACK,LCD_SIZE);				
				break;		
         }
	}
	return 0;	

return 0;
}
