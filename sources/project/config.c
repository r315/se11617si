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

void PRINT_Field(uint32_t field, uint32_t format, uint8_t select){
    if(select)
        LCD_SetColors(CFG_BC, CFG_FC); // invert colors

    LCD_WriteInt(field, format);
    LCD_SetColors(CFG_FC, CFG_BC);
}

void PRINT_FullDate(struct tm *rtc, uint8_t select){
    POSITION_DATE;    
    
    PRINT_Field(rtc->tm_hour, TIME_FORMAT, (select == HOUR)? ON : OFF);
    LCD_WriteChar(':');
    PRINT_Field(rtc->tm_min, TIME_FORMAT, (select == MINUTES)? ON : OFF);
    LCD_WriteChar(' ');
    
    if(select == WEEKDAY)
        LCD_SetColors(CFG_BC, CFG_FC);
    LCD_WriteString((char*)&wdays[rtc->tm_wday][0]);
    LCD_SetColors(CFG_FC, CFG_BC);    
    LCD_WriteChar(' ');
    
    PRINT_Field(rtc->tm_mday, TIME_FORMAT, (select == MDAY)? ON : OFF);
    LCD_WriteChar('-');
    PRINT_Field(rtc->tm_mon, TIME_FORMAT, (select == MONTH)? ON : OFF);
    LCD_WriteChar('-');
    PRINT_Field(rtc->tm_year, TIME_FORMAT, (select == YEAR)? ON : OFF);
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
    PRINT_FullDate(cur_time, field);
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
