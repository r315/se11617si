#include <timer.h>
#include <button.h>
#include <spi.h>
#include <lcd.h>


int main(void){

	PLL_Init();   //if used must be the first peripheral to initialize
    
    TIMER0_Init(MS_IN_1S);

    BUTTON_Init(BUTTON_DEFAULT_HOLD_TIME);

    SPI_Init(1000, SPI_8BIT); // lcd must be initialyze with low speed and 8bit transfers

    LCD_Init();

    SPI_Init(SPI_MAX_FREQ, SPI_16BIT); //after init use full speed

    LCD_Clear(BLACK);

    LCD_SetColors(GREEN,BLACK);
        

	while(1){	
        BUTTON_Hit();

        if(BUTTON_GetButtonEvents() == BUTTON_RELEASED)LCD_Clear(BLACK);
		
		switch(BUTTON_Read()){
			case BUTTON_L:
	            switch(BUTTON_GetButtonEvents()){
                    case BUTTON_PRESSED:
                        LCD_Goto(0,0);  
                        LCD_WriteString("Pressed");
                        break;
                    case BUTTON_TIMING:
                        LCD_Goto(0,16);  
                        LCD_WriteString("Timing");
                        break;
                    case BUTTON_HOLD:
                        LCD_Goto(0,32);  
                        LCD_WriteString("Hold");
                        break;
                    case BUTTON_RELEASED:
                        LCD_Clear(BLACK);
                        break;

                }
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
				if(BUTTON_GetButtonEvents() != BUTTON_HOLD)
					break;
				LCD_Fill(BLACK,LCD_SIZE);				
				break;		
         }
	}
	return 0;	

return 0;
}
