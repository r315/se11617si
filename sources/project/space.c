#include <lcd.h>
#include <stdint.h>
#include "space.h"


typedef struct _sprite{
    int x;
    int y;
    int alive;
    int color;
    uint8_t *data;
}Sprite;

static const char title[]={
    "           GAME\n\n"
    "F   -  fire\n"
    "S   -  save & exit\n"
    "L|R -  move\n"
};


void popSpace(void){
    LCD_Clear(BLACK);
    LCD_SetColors(RED,BLACK);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);
    LCD_SetColors(GREEN,BLACK);   
}

void space(int b){

}
