#include <lcd.h>
#include <stdint.h>
#include <button.h>
#include <timer.h>
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

Sprite tank;
int state;

void drawSprite(Sprite *sp){
uint16_t i;
uint8_t *data;
    if(sp->alive){
        data = sp->data;                
        LCD_Window(sp->x,sp->y,16,16);        
        for(i = 0; i < SPRITE_SIZE / 2; i++, data+=1){
            LCD_Data(pallete[*data & 15]);
            LCD_Data(pallete[(*data)>>4 & 15]);
        }
        
    }
    
}

void eraseSprite(Sprite *sp){
uint16_t i;
uint8_t *data;    
    data = sp->data;                
    LCD_Window(sp->x,sp->y,16,16);        
    for(i = 0; i < SPRITE_SIZE; i++, data+=1){
        LCD_Data(BLACK);   //TODO: remove cs setting  on lcddata function
    }   
}

void popSpace(void *ptr){
    LCD_Clear(BLACK);
    LCD_SetColors(RED,BLACK);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);
    LCD_SetColors(GREEN,BLACK);  
    
    tank.data = (uint8_t*)spriteTank;
    tank.x = (LCD_W/2)-8;
    tank.y = LCD_H-16;
    tank.alive = 1;
    
    
}

void space(int b){
static uint32_t frametime;


    if(frametime > TIMER0_GetValue())
        return;    

    switch(b){
        case BUTTON_L:
           eraseSprite(&tank);
            tank.x = tank.x? tank.x-1 : tank.x;
           drawSprite(&tank); 
        break;
        case BUTTON_R:
            eraseSprite(&tank);
            tank.x = tank.x < LCD_W - 16? tank.x+1 : tank.x;
           drawSprite(&tank); 
        break;
        case BUTTON_F:    
        
        
        default: break;
    }
    
    frametime = TIMER0_GetValue() + 20;

}
