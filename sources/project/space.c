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

void LCD_OffsetWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	LCD_Window(SCREEN_SX + x, SCREEN_SY + y, w, h);
}

void drawSprite(Sprite *sp){
uint16_t i;
uint8_t *data;
	
	data = sp->data;                
	LCD_OffsetWindow(sp->x, sp->y,SPRITE_W,SPRITE_H);        
	//GPIO_Clr(3); //LCD_CS
	//GPIO_Set(9); //LCD_RS
	for(i = 0; i < SPRITE_SIZE; i++, data+=1){		
		LCD_Data(pal1[*data]);
        //SPI_Send(pal1[*data]);
	}
	//GPIO_Set(3); //LCD_CS
}

void loadTank(Sprite *sp){
	sp->data = (uint8_t*)TANK_DATA;
    sp->x = (SCREEN_W/2)-8;
    sp->y = SCREEN_H-16;
}

void moveTank(Sprite *tk, int8_t dir){
int newx;
int8_t d;

	newx = tk->x + dir;
	
	if(newx > (SCREEN_W-SPRITE_W) || newx < 0)
		return;
		
	d = (dir < 0)? -dir : dir;

	// erase only necessary data from old position		
	if(newx >= tk->x)
		LCD_OffsetWindow(tk->x, tk->y, d, SPRITE_H);
	else
		LCD_OffsetWindow(newx+SPRITE_W, tk->y, d, SPRITE_H);	
		
	LCD_Fill(BGCOLOR, d * SPRITE_H);
	
	tk->x = newx;
	drawSprite(tk);	
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
