//Using SDL and standard IO 
#include <SDL2/SDL.h> 
#include <stdio.h> 

#include "lcdsdl.h"
#include <display.h>

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;

void LCD_Init(void){

   if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
   }
   else{
		window = SDL_CreateWindow( windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LCD_W, LCD_H, SDL_WINDOW_SHOWN ); 
    	if( window == NULL ) { 
    		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
    	}
    	else { 
    		//Get window surface 
    		screenSurface = SDL_GetWindowSurface( window ); 
    		//Fill the surface white
    		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) ); 
    		//Update the surface 
    		SDL_UpdateWindowSurface( window );
		}
	}	
}


void LCD_Close(void){
	SDL_DestroyWindow( window ); 
	//Quit SDL subsystems 
	SDL_Quit(); 
}
