#include <timer.h>
#include <button.h>
#include <display.h>
#include <spi.h>


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
