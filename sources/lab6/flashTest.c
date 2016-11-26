#include <stdio.h>
#include <spi.h>
#include <led.h>
#include <lcd.h>
#include <timer.h>
#include <rtc.h>
#include <button.h>

#define MEM_ADDRESS_FORMAT (4<<8) | 16
#define MEM_DATA_FORMAT (2<<8) | 16

void MEM_Dump(uint8_t *start, uint32_t len){
uint32_t i;   

    LCD_Goto(0,0);
    while(len){
        LCD_WriteInt((uint32_t)start, MEM_ADDRESS_FORMAT);
        LCD_WriteChar(':');
        for(i=0; i < 16 && len > 0;i++){
            LCD_WriteChar(' ');
            LCD_WriteInt((*start, MEM_DATA_FORMAT);
            len--;
        }
        start += i;
        LCD_NewLine();
    }

}


static out[20];
int main(int argc, char *argv[]){
struct tm rtc;

    FLASH_EraseSectors(0,0);
	rtc.tm_sec = 50;
	rtc.tm_min = 25;
	rtc.tm_hour = 01;
	rtc.tm_mday = 10;
	rtc.tm_mon = 11;
	rtc.tm_year = 2016;
	rtc.tm_wday = 0;
   
    TIMER0_Init(MS_IN_1S);	

  	LED_Init(LED, LED_OFF);

  	BUTTON_Init();

  	RTC_Init(&rtc);

	SPI_Init(1000, SPI_8BIT); // lcd must be initialyze with low speed and 8bit transfers

	LCD_Init();

	SPI_Init(SPI_MAX_FREQ, SPI_16BIT);

	LCD_Clear(BLUE);

	LCD_SetColors(RED,BLUE);

        

	while(1){


	
	}
	return 0;
}
 
