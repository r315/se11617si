#include <time.h>
#include <lcd.h>
#include <rtc.h>
#include <button.h>
#include "config.h"

//TODO: fix field indicator and save to flash


static struct tm alarm, *cur_time;
static uint8_t field;
const char wdays[7][4]={"mon","tue","wed","thu","fri","sat","sun"};
static const char title[]={
    "           CONFIG\n\n"    
};

void PRINT_RtcTime(struct tm *rtc, uint8_t format){
    LCD_WriteInt(rtc->tm_hour, TIME_FORMAT);
    LCD_WriteChar(':');
    LCD_WriteInt(rtc->tm_min, TIME_FORMAT);
    if(format == RTC_TIME_HHMMSS){
        LCD_WriteChar(':');
        LCD_WriteInt(rtc->tm_sec, TIME_FORMAT);
    }
}

void PRINT_Rtc(struct tm *rtc, uint8_t data){   
   switch(data){      
      case RTC_DATETIME:
         PRINT_RtcTime(rtc,RTC_TIME_HHMM);
         LCD_WriteChar(' ');
                  
      case RTC_DATE:
         LCD_WriteInt(rtc->tm_mday, TIME_FORMAT);
         LCD_WriteChar('-');
         LCD_WriteInt(rtc->tm_mon, TIME_FORMAT);
         LCD_WriteChar('-');
         LCD_WriteInt(rtc->tm_year, YEAR_FORMAT);
         break;     
         
      case RTC_TIME_HHMM:
         PRINT_RtcTime(rtc, RTC_TIME_HHMM);
         break;
      
      case RTC_TIME_HHMMSS:
         PRINT_RtcTime(rtc,RTC_TIME_HHMMSS);        
         break;      
         
      case RTC_WDAY:         
         LCD_WriteString((char*)&wdays[rtc->tm_wday][0]);         
         break;      
   }   
}

void PRINT_FullDate(struct tm *rtc){
    LCD_Goto(16,64);
    PRINT_Rtc(rtc, RTC_TIME_HHMM);                
    LCD_WriteChar(' ');
    PRINT_Rtc(rtc, RTC_WDAY);      
    LCD_WriteChar(' ');
    PRINT_Rtc(rtc, RTC_DATE);    
}

void changeField(int32_t *fld, uint32_t max, int8_t step){
    *fld = (*fld + step);
    *fld = *fld % (max+1);
    
    if(*((uint32_t*)fld) > max)
        *fld = max;	
}

void setTime(struct tm *rtc, uint8_t fld, signed char step){  
    switch(fld){
        case HOUR:      changeField((int32_t *)&rtc->tm_hour,23, step); break;
        case MINUTES:   changeField((int32_t *)&rtc->tm_min,59, step); break;
        case WEEKDAY:   changeField((int32_t *)&rtc->tm_wday,6, step); break;        
        case MDAY:      changeField((int32_t *)&rtc->tm_mday,31, step); break;        
        case MONTH:     changeField((int32_t *)&rtc->tm_mon,12, step); break;        
        case YEAR:      changeField((int32_t *)&rtc->tm_year,2060, step); break;
   }   
}

void setIndicator(uint8_t fld){
    LCD_Goto(8,80);
    LCD_WriteString("                 ");
    LCD_Goto(8+(16*fld),80);
    LCD_WriteChar('^');    
}

void popConfig(void *ptr){  
    field = HOUR;
    cur_time = (struct tm*)ptr;
    
    RTC_GetValue(cur_time);
    RTC_GetAlarmValue(&alarm);
 
    LCD_Clear(BLACK);
    LCD_SetColors(RED,BLACK);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);
    LCD_SetColors(GREEN,BLACK);
    PRINT_FullDate(cur_time);
}

int config(int b){
signed char step;

    if(BUTTON_GetEvents() != BUTTON_PRESSED)
        return 1;

    switch(b){
        case BUTTON_L: step = -1; break;
        
        case BUTTON_R: step =  1; break;
        
        case BUTTON_F: 
            if((++field) == (YEAR + 1))
                field = HOUR;
            step = 0;
            break;       
        
        case BUTTON_S:        
            return 0;
        
        default: return 1;
    } 
   
    setTime(cur_time, field, step);
    
    PRINT_FullDate(cur_time);
    
    setIndicator(field);
    return 1;
}
