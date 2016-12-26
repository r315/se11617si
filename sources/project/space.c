#include <lcd.h>
#include <stdint.h>
#include <button.h>
#include <timer.h>
#include "space.h"
#include "sprites/sprites.h"

#include <gpio.h>
#include <spi.h>

void LCD_Fill(uint16_t color, uint32_t n);

typedef struct _sprite{
	int x;
	int y;	
	uint8_t *data;
	uint8_t alive;
}Sprite;

typedef struct projectile{
	int x;
	int y;
	uint16_t color;
	uint8_t inmotion;
}Projectile;

static const char title[]={
    "      # Space Invaders #\n\n"    
};

void LCD_Data(uint16_t color);

Sprite tank, aliens[36];
Projectile projectiles[5];

int state;

void drawTank(Tank *tk){
uint16_t i;
uint8_t *data;
	
	data = tk->data;                
	LCD_Window(tk->x,tk->y,16,16);        
	//GPIO_Clr(3);
	//GPIO_Set(9);
	for(i = 0; i < SPRITE_SIZE; i++, data+=1){
		//LCD_Data(pallete[*data & 15]);
		//LCD_Data(pallete[(*data)>>4 & 15]);
		//SPI_Send(pal1[*data & 15]);
		//SPI_Send(pal1[(*data)>>4 & 15]);
		LCD_Data(pal1[*data]);
	}
	//GPIO_Set(3);
}

void moveTank(Tank *tk, int8_t dir){
int newx;
int8_t d;

	newx = tk->x + dir;
	
	if(newx > (SCREEN_W-SPRITE_W) || newx < 0)
		return;
		
	d = (dir < 0)? -dir : dir;

	// erase only necessary data from old position		
	if(newx >= tk->x)
		LCD_Window(tk->x, tk->y, d, SPRITE_H);
	else
		LCD_Window(newx+SPRITE_W, tk->y, d, SPRITE_H);	
		
	LCD_Fill(BGCOLOR, d * SPRITE_H);
	
	tk->x = newx;
	drawTank(tk);	
}

void moveProjectile(Projectile *pj, int8_t dir){
int newy;

	if(!pj->inmotion)
		return;
		
	newy = pj->y + dir;
	
	if(newy > (SCREEN_H-SPRITE_H) || newy < 0){
		pj->inmotion = 0;
		return;
	}
	
	LCD_Window(pj->x, pj->y, 1, 4);
	LCD_Fill(BGCOLOR, 4);	
	
	pj->y = newy;
	
	LCD_Window(pj->x, pj->y, 1, 4);
	LCD_Fill(WHITE, 4);		
}

void newProjectile(Projectile *pjs, uint8_t n, int x, int y){
uint8_t i;
	for(i = 0; i < n; i++){
		if(!pjs[i].inmotion){
			pjs[i].x = x;
			pjs[i].y = y;
			pjs[i].inmotion = ON;
			return;
		}	
	}	
}

void popSpace(void *ptr){
    LCD_Clear(BLACK);
    LCD_SetColors(RED,BLACK);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);
    LCD_SetColors(GREEN,BLACK);  
    
    tank.data = (uint8_t*)spcinv;
    tank.x = (LCD_W/2)-8;
    tank.y = LCD_H-16;
    drawTank(&tank);    
}

void space(int b){
static uint32_t frametime;	
uint8_t n;
	
    if(TIMER0_GetValue() > frametime){
		for(n=0; n < MAX_PROJECTILES; n++)		
			moveProjectile(&projectiles[n],-4);
			
		frametime = TIMER0_GetValue() + 20;
	}
	else{
		if(BUTTON_GetEvents() == BUTTON_HOLD)
		return;    
	}
	
    switch(b){
        case BUTTON_L:	moveTank(&tank,-2); break;
        case BUTTON_R:	moveTank(&tank,2); break;            
        break;
        case BUTTON_F: newProjectile(projectiles, MAX_PROJECTILES, tank.x + SPRITE_W/2, tank.y - 4);
				
        
        default: break;
    }
    
    

}
