#include <lcd.h>
#include <stdint.h>
#include <button.h>
#include <timer.h>
#include "proj.h"
#include "space.h"
#include "sprites/sprites.h"

#include <gpio.h>
#include <spi.h>

static const char title[]={
    "      # Space Invaders #\n\n"    
};

GameData *gamedata;
void LCD_Data(uint16_t color);
void LCD_Fill(uint16_t color, uint32_t n);

void LCD_OffsetWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
    LCD_Window(SCREEN_SX + x, SCREEN_SY + y, w, h);
}

void drawSprite(Sprite *sp){
uint16_t i;
uint8_t *data;

    data = sp->data;                
    LCD_OffsetWindow(sp->x, sp->y,SPRITE_W,SPRITE_H);

    #ifdef _EMU_
    for(i = 0; i < SPRITE_SIZE; i++, data+=1){       
        LCD_Data(pal1[*data]);
    }
    #else
    GPIO_Clr(3); //LCD_CS
    GPIO_Set(9); //LCD_RS
    for(i = 0; i < SPRITE_SIZE; i++, data+=1){
        SPI_Send(pal1[*data]);
    }
    GPIO_Set(3); //LCD_CS
    #endif
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

    if(newy > (SCREEN_H-SPRITE_H) || newy < -SPRITE_H){
        pj->inmotion = 0;
        return;
    }

    LCD_OffsetWindow(pj->x, pj->y, 1, 4);
    LCD_Fill(BGCOLOR, 4);

    pj->y = newy;

    LCD_OffsetWindow(pj->x, pj->y, 1, 4);
    LCD_Fill(pj->color, 4);
}

void newProjectile(Projectile *proj, int x, int y, uint16_t color){
uint8_t i;
    for(i = 0; i < MAX_PROJECTILES; i++){
        if(!proj[i].inmotion){
            proj[i].x = x;
            proj[i].y = y;
            proj[i].color = color;
            proj[i].inmotion = ON;
            return;
        }	
    }	
}

void loadAliens(Sprite *als, const uint8_t *al, uint16_t y){
uint8_t i;
uint16_t x = SPRITE_W;
    for(i=0; i < MAX_ALIENS; i++, al+=1){
        als[i].x = x;
        als[i].y = y;
        als[i].type = (*al) - 1;
        als[i].data = (uint8_t*)(SPRITES_DATA + (als[i].type * SPRITE_SIZE));
        als[i].alive = ON;
        x += SPRITE_W;
        if(x > (SCREEN_W-(SPRITE_W*2)) ){
            x = SPRITE_W;
            y += SPRITE_H;
        }
    }
}

int8_t moveAliens( Sprite *als, const uint8_t *alienFrame, int8_t dir, int8_t height){
uint8_t i;

    if(((dir < 0) && (als[0].x <= 0)) || (dir > 0 && als[MAX_ALIENS-1].x >= SCREEN_W-SPRITE_W))
        dir  = -dir;

    for(i = 0; i< MAX_ALIENS; i++, alienFrame +=  1){
        als[i].x += dir;
        als[i].y += height;
        
        if(als[i].alive){
            drawSprite(&als[i]);
            als[i].data = (uint8_t*)(SPRITES_DATA + (((*alienFrame) - 1) * SPRITE_SIZE));
        }
        else
        {
            LCD_OffsetWindow(als[i].x, als[i].y, SPRITE_W, SPRITE_H);	
            LCD_Fill(BGCOLOR, SPRITE_SIZE);
        }
    }
    return dir;
}

uint8_t checkColision(Projectile *proj, Sprite *als){
uint8_t i;
uint8_t score;

    if(proj->inmotion == OFF)
        return 0;   
    
    for(i = 0; i< MAX_ALIENS; i++){
        if(als[i].alive){
            if(als[i].x <= proj->x && (als[i].x + SPRITE_W) >= proj->x){
                if(als[i].y <= proj->y && (als[i].y + SPRITE_H) >= proj->y){
                    als[i].alive = OFF;
                    proj->inmotion = OFF;
                    score = als[i].type + 1;
                    //printf("Score: %u\n",score);
                    return score;
                }
            } 
        }
    }
    return 0;
}

void updateScore(uint32_t scr){
    LCD_Goto(SCREEN_SX + 3, SCREEN_SY + 3);
    LCD_WriteInt(scr, SCORES_FORMAT);
    
}

void newGame(GameData *gd){    
    loadTank(&gd->tank);    
    loadAliens(gd->aliens, Aliens0, SPRITE_H * 3);	
    gd->score = 0;    
}

void popSpace(void *ptr){

    LCD_Clear(UBUNTU);
    LCD_SetColors(WHITE,UBUNTU);
    LCD_Goto(0,0);    
    LCD_WriteString((char*)title);    

    BUTTON_SetHoldTime(80);

    LCD_OffsetWindow(0, 0, SCREEN_W, SCREEN_H);
    LCD_Fill(BGCOLOR,SCREEN_W * SCREEN_H);

    gamedata = (GameData*)ptr; 
    moveTank(&gamedata->tank,0);   
    moveAliens(gamedata->aliens, Aliens1, 0,0);
    updateScore(gamedata->score);
}


void space(int b){
static uint32_t frametime;	
uint8_t n;
static int8_t dir = -1;
static uint8_t speed = SPEED;
static uint8_t f;
    
    if(TIMER0_GetValue() > frametime){
        
        switch(b){
            case BUTTON_L:  moveTank(&gamedata->tank,-1); break;
            case BUTTON_R:  moveTank(&gamedata->tank,1); break;
            case BUTTON_F:  newProjectile(gamedata->tankprojectiles, gamedata->tank.x + SPRITE_W/2, gamedata->tank.y - 4, PINK); break;            
            
            case (BUTTON_F | BUTTON_L): 
                moveTank(&gamedata->tank,-1);
                newProjectile(gamedata->tankprojectiles, gamedata->tank.x + SPRITE_W/2, gamedata->tank.y - 4, PINK);
                break;
            
            case (BUTTON_F | BUTTON_R):
                moveTank(&gamedata->tank,1);
                newProjectile(gamedata->tankprojectiles, gamedata->tank.x + SPRITE_W/2, gamedata->tank.y - 4, PINK);
                break;
            
            default: break;
        }
        
        for(n=0; n < MAX_PROJECTILES; n++){
            moveProjectile(&gamedata->tankprojectiles[n],-1);
            gamedata->score += checkColision(&gamedata->tankprojectiles[n], gamedata->aliens);
            updateScore(gamedata->score);
        }
    
        if(!(--speed)){
            dir = moveAliens(gamedata->aliens, (f & 4)? Aliens0 : Aliens1, dir,0); 
            speed = SPEED;
            f++;
        }  
        //TODO: implement aliens down and shot
                    
        frametime = TIMER0_GetValue() + 20;
    }
}
