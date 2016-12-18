#include <lcd.h>
#include <time.h>
#include <rtc.h>
#include <timer.h>
#include "idle.h"
#include "config.h"

#define MAX_TOP_SCORES 3
#define SCORES_FORMAT (3<<8) | 10

static const char title[]={
    "           IDLE\n\n"
    "F   -  start new Game\n"
    "S   -  Load Game\n"
    "L&R -  for config\n"
    "Top Scores:\n"
};

static uint32_t highScores;
static uint32_t updateTime;

void PRINT_DateTime(struct tm *rtc){
    LCD_WriteInt(rtc->tm_mday, TIME_FORMAT);
    LCD_WriteChar('/');
    LCD_WriteInt(rtc->tm_mon, TIME_FORMAT);
    LCD_WriteChar('/');
    LCD_WriteInt(rtc->tm_year, YEAR_FORMAT);  
    LCD_WriteChar(' ');     
    LCD_WriteInt(rtc->tm_hour, TIME_FORMAT);
    LCD_WriteChar(':');
    LCD_WriteInt(rtc->tm_min, TIME_FORMAT);
    LCD_WriteChar(':');
    LCD_WriteInt(rtc->tm_sec, TIME_FORMAT);  
}

/**
 * @brief high scores are stored on one integer so is 8-bit one high score
 * */
void PRINT_HighScores(int scores){   
uint8_t n = MAX_TOP_SCORES;
    while(n--){
        LCD_WriteInt(scores & 255, SCORES_FORMAT);
        LCD_NewLine();
        LCD_WriteString("          "); //TODO: make dynamic position
        scores >>= 8;
    }
}

void popIdle(void *ptr){  
    highScores = *((int*)ptr);  
    updateTime = TIMER0_GetValue() - 1000;  //force update
    LCD_Clear(BLACK);
    LCD_SetColors(RED,BLACK);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);
    
    LCD_Goto(80,96);
    LCD_SetColors(BLUE,BLACK);
    PRINT_HighScores(highScores);
    LCD_SetColors(GREEN,BLACK);   
    BUTTON_SetHoldTime(ENTER_CONFIG_TIME);       
}

void idle(void){
struct tm rtc;
    //TODO: interrupt on rtc for seconds
    if( TIMER0_Elapse(updateTime) > 1000){
        RTC_GetValue(&rtc);   
        LCD_Goto(10,LCD_H-16);        
        PRINT_DateTime(&rtc);                
        updateTime = TIMER0_GetValue();
    }
}
