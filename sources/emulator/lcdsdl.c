//Using SDL and standard IO 
#include <SDL2/SDL.h> 
#include <stdio.h> 

#include "lcdsdl.h"
#include <display.h>

#define LCD_FISICAL_W 240
#define LCD_FISICAL_H 320

#define LCD_OFFSETX (LCD_FISICAL_W/2) - (LCD_W/2) //center lcd window
#define LCD_OFFSETY (LCD_FISICAL_H/2) - (LCD_H/2)

struct LCD{
	SDL_Window *window;
	SDL_Surface *surface;
	uint32_t w;
	uint32_t h;
	uint32_t wx;			//wrap x
	uint32_t wy;			//wrap y
	uint32_t ww;			//wrap w
	uint32_t wh;			//wrap h
	uint32_t mx;			//memory current x
	uint32_t my;			//memory current y	
}lcd;



void LCD_Init(void){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return; 
	}

	lcd.w = LCD_W;
	lcd.h = LCD_H;	
  
	lcd.window = SDL_CreateWindow( 	windowTitle, 
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED, 
									LCD_FISICAL_W, 
									LCD_FISICAL_H, 
									SDL_WINDOW_SHOWN); 
	if( lcd.window == NULL ) { 
    	printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return;
   	}
    	
    lcd.surface = SDL_GetWindowSurface( lcd.window ); 
	fprintf(stdout,"Window size: %dx%d %dbpp\n",lcd.surface->w, lcd.surface->h, lcd.surface->format->BitsPerPixel);    		
	SDL_FillRect(lcd.surface, NULL, SDL_MapRGB(lcd.surface->format, 0x30, 0x0A, 0x24 ) );     		
    LCD_Update();	
}

void LCD_Close(void){
	SDL_DestroyWindow(lcd.window); 
	SDL_Quit(); 
}

void LCD_Update(void){
	SDL_UpdateWindowSurface(lcd.window);
}

void LCD_Rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
SDL_Rect rect;
	rect.x=x;
	rect.y=y;
	rect.w=w;
	rect.h=h;

	SDL_FillRect(lcd.surface, 
			&rect,
			SDL_MapRGB( lcd.surface->format, 0xFF, 0xFF, 0xFF ) );     		
}

void LCD_Fill(uint16_t color, uint32_t n){
	while(n--)
		LCD_Data(color);
}

void LCD_SetWrap(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	lcd.wx = x;
    lcd.wy = y;
	lcd.ww = x + (w-1);
    lcd.wh = y + (h-1);	

	lcd.mx = lcd.wx;
    lcd.my = lcd.wy;   
}

//-------------------------------------------------------------
//        RRRRRGGGGGGBBBBB 
//        BBBBBGGGGGGRRRRR
//RRRRRRRRGGGGGGGGBBBBBBBB
//-------------------------------------------------------------
void LCD_Data(uint16_t color)
{
   uint32_t *pixels = (uint32_t *)lcd.surface->pixels;    
   
	if(lcd.mx >= lcd.wx && lcd.mx <= lcd.ww && 
       lcd.my >= lcd.wy && lcd.my <= lcd.wh &&
       lcd.mx < lcd.w && lcd.my < lcd.h)
	{
    	pixels[ ((lcd.my + LCD_OFFSETY) * LCD_FISICAL_W) + lcd.mx + LCD_OFFSETX ] = (uint32_t) ( ((color&0xf800)<<8) | ((color&0x7e0)<<5) | ((color&0x1f)<<3) );   
        if(lcd.mx == lcd.ww){
            lcd.mx = lcd.wx;
            if(lcd.my == lcd.wh) lcd.my = lcd.wy;
            else lcd.my++;
        }
        else lcd.mx++;
    }   
}


