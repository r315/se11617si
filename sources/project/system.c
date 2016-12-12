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


const int defaultRtc[]={0,2,0,0,0,0,0,0,0,0,0};

void SYS_Init(void){
      
    //PLL_Init();   //if used must be the first peripheral to initialize
    
    TIMER0_Init(MS_IN_1S);

    LED_Init(LED, LED_ON);

    BUTTON_Init();

    SPI_Init(1000, SPI_8BIT); // lcd must be initialyze with low speed and 8bit transfers

    LCD_Init();

    SPI_Init(SPI_MAX_FREQ, SPI_16BIT); //after init use full speed

    LCD_Clear(RGB(6,2,4));

    LCD_SetColors(GREEN,BLACK);
    
    memset((void*)defaultRtc, 0 , sizeof(struct tm));	// initialize rtc structures     
    
    RTC_Init((struct tm*)&defaultRtc);
}
