#include <lcd.h>
#include <time.h>
#include <rtc.h>
#include <timer.h>
#include "idle.h"

static const char title[]={
    "           IDLE\n\n"
    "F   -  start new Game\n"
    "S   -  Load Game\n"
    "L&R -  for config\n"
};


void PRINT_Rtc(){
struct tm rtc;    
    LCD_Goto(80,96);    
    RTC_GetValue(&rtc);    
    
    LCD_WriteInt(rtc.tm_hour, TIME_FORMAT);
    LCD_WriteChar(':');
    LCD_WriteInt(rtc.tm_min, TIME_FORMAT);
    LCD_WriteChar(':');
    LCD_WriteInt(rtc.tm_sec, TIME_FORMAT);
}

void popIdle(void){
    LCD_Clear(BLACK);
    LCD_SetColors(RED,BLACK);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);
    LCD_SetColors(GREEN,BLACK);    
}

void idle(void){
static uint32_t time;
    //TODO: interrupt on rtc for seconds
    if( TIMER0_Elapse(time) > 1000){
        PRINT_Rtc();
        time = TIMER0_GetValue();
    }

}
