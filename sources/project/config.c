#include <time.h>
#include <lcd.h>
#include <rtc.h>
#include "config.h"


static const char title[]={
    "           CONFIG\n\n"
    
};

void popConfig(void *ptr){   
    LCD_Clear(BLACK);
    LCD_SetColors(RED,BLACK);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);
    LCD_SetColors(GREEN,BLACK);
    
}

int config(int b){


return 1;
}
