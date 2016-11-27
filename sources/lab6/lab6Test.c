#include <stdio.h>
#include <spi.h>
#include <led.h>
#include <lcd.h>
#include <timer.h>
#include <rtc.h>
#include <button.h>
#include <flash.h>

#define MEM_BASE 16
#define MEM_ADDRESS_FORMAT (4<<8) | MEM_BASE
#define MEM_DATA_FORMAT (2<<8) | MEM_BASE
#define MEM_MAX_COLS 8

void MEM_Dump(uint8_t *start, uint32_t len){
uint32_t i;   

    LCD_Goto(0,0);
    while(len){
        LCD_WriteInt((uint32_t)start, MEM_ADDRESS_FORMAT);
        LCD_WriteChar(':');
        for(i=0; i < MEM_MAX_COLS && len > 0;i++){
            LCD_WriteChar(' ');
            LCD_WriteInt(*start, MEM_DATA_FORMAT);
            len--;
        }
        start += i;
        LCD_NewLine();
    }

}

void LED_Blink(uint32_t ms){
      LED_SetState(LED_ON);
      TIMER0_DelayMs(ms);
      LED_SetState(LED_OFF);
}

static out[20];
int main(int argc, char *argv[]){
struct tm rtc;

	rtc.tm_sec = 50;
	rtc.tm_min = 25;
	rtc.tm_hour = 01;
	rtc.tm_mday = 10;
	rtc.tm_mon = 11;
	rtc.tm_year = 2016;
	rtc.tm_wday = 0;
   
    TIMER0_Init(MS_IN_1S);	

  	LED_Init(LED, LED_ON);

  	BUTTON_Init();

  	RTC_Init(&rtc);

	SPI_Init(1000, SPI_8BIT); // lcd must be initialyze with low speed and 8bit transfers

	LCD_Init();

	SPI_Init(SPI_MAX_FREQ, SPI_16BIT);

	LCD_Clear(BLACK);

	LCD_SetColors(GREEN,BLACK);      

	while(1){
        switch(BUTTON_Read()){
			case BUTTON_L:
				LED_Blink(500);               
                MEM_Dump((uint8_t *)0,128);
		  		break;
			case BUTTON_R:
				LED_Blink(1000);
                MEM_Dump((uint8_t *)128,128);
		  		break;
			case BUTTON_F:
				LED_Blink(1500);
                MEM_Dump((uint8_t *)256,128);
		  		break;
			case BUTTON_S:
				LED_Blink(2000);
                LCD_Goto(0,LCD_H-20);
                LCD_WriteInt(FLASH_EraseSectors(0,0),MEM_DATA_FORMAT);
		  		break;		         
			case BUTTON_L | BUTTON_R:
				if(BUTTON_GetButtonsEvents() != BUTTON_HOLD)
					break;
				LED_Blink(30);
				TIMER0_DelayMs(70);
				LED_Blink(30);
				break;		
             
         }	
	}
	return 0;
}
 
