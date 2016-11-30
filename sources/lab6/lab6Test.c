#include <stdio.h>
#include <string.h>
#include <spi.h>
#include <led.h>
#include <lcd.h>
#include <timer.h>
#include <rtc.h>
#include <button.h>
#include <flash.h>
#include <time.h>

#define SAVED_RTC (13*FLASH_SECTOR_SIZE)

#define BASE_HEX 16
#define MEM_ADDRESS_FORMAT (4<<8) | BASE_HEX
#define MEM_DATA_FORMAT (2<<8) | BASE_HEX
#define MEM_MAX_COLS 8

#define BASE_DEC 10
#define TIME_FORMAT (2<<8) | BASE_DEC
typedef enum{
   RTC_DATETIME,
   RTC_TIME_HHMM,
   RTC_TIME_HHMMSS,
   RTC_DATE,
}RTC_FORMATS;
   


void restoreRtc(struct tm *rtc){
   memcpy((uint8_t*)rtc,(uint8_t *)SAVED_RTC,sizeof(struct tm));
}

void setRtc(struct tm *rtc){
   
}

void PRINT_RtcTime(struct tm* rtc){
    LCD_WriteInt(rtc->tm_hour, TIME_FORMAT);
    LCD_WriteChar(':');
    LCD_WriteInt(rtc->tm_min, TIME_FORMAT);
}

void PRINT_RtcDate(struct tm* rtc){
    LCD_WriteInt(rtc->tm_mday, TIME_FORMAT);
    LCD_WriteChar('-');
    LCD_WriteInt(rtc->tm_mon, TIME_FORMAT);
    LCD_WriteChar('-');
    LCD_WriteInt(rtc->tm_year, (4<<8) | BASE_DEC);
}

void PRINT_Rtc(struct tm* rtc, uint8_t data){
   
   switch(data){      
      case RTC_DATETIME:
         PRINT_RtcTime(rtc);
         LCD_WriteChar(' ');
                  
      case RTC_DATE:
         PRINT_RtcDate(rtc);
         break;     
         
      case RTC_TIME_HHMM:
         PRINT_RtcTime(rtc);
         break;
      
      case RTC_TIME_HHMMSS:
         PRINT_RtcTime(rtc);
         LCD_WriteChar(':');
         LCD_WriteInt(rtc->tm_sec, TIME_FORMAT);
         break;       
   }   
}

void PRINT_Mem(uint8_t *start, uint32_t len){
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

void Acerto(void){
   
   
}

int main(int argc, char *argv[]){
struct tm rtc;
   restoreRtc(&rtc);
	
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
                PRINT_Mem((uint8_t *)0,128);
		  		break;
			case BUTTON_R:
				LED_Blink(1000);
                PRINT_Mem((uint8_t *)128,128);
		  		break;
			case BUTTON_F:
				LED_Blink(1500);
                PRINT_Mem((uint8_t *)256,128);
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
      
      switch(main_state){
         
         case ACERTO:
            Acerto();            
            break;
         
         case ALARM:
            
            break;
         
         default:         
      }
	}
	return 0;
}
 
