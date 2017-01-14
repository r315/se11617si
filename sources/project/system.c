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
#include <clock.h>

const int defaultRtc[]={0,0,0,0,0,2010,0,0,0,0,0};

void SYS_Init(void){
    
    SC->APBDIV = APBDIV_2; // PCLK = CCLK / APBDIB
      
    PLL_Init(MSEL, PSEL);   //if used must be the first peripheral to initialize
    
    TIMER0_Init(MS_IN_1S);

    LED_Init(LED, LED_OFF);

    BUTTON_Init(BUTTON_DEFAULT_HOLD_TIME-1500);

    SPI_Init(1000, SPI_8BIT); // lcd must be initialyze with low speed and 8bit transfers

    LCD_Init();

    SPI_Init(SPI_MAX_FREQ, SPI_16BIT); //after init use full speed
    
    LCD_SetColors(GREEN,BLACK);
        
    RTC_Init((struct tm*)&defaultRtc);
}
