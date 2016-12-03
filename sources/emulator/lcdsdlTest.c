#include <SDL2/SDL.h> 
#include <stdio.h> 
#include <lcd.h>
#include "lcdsdl.h"

#define BUTTON_L (1<<11)
#define BUTTON_R (1<<13)
#define BUTTON_F (1<<12)
#define BUTTON_S (1<<15)

#define loop() BUTTON_Read() != SDLK_q
int BUTTON_Read(void);
int BUTTON_GetButtonsEvents(void);

int main(int argc, char *argv[]){

   LCD_Init();
   LCD_SetColors(GREEN,BLACK);
  // LCD_Pixel(10,10,RED);
   LCD_OpenFrame(0,0,LCD_W,LCD_H);
   LCD_Fill(BLUE,LCD_SIZE);
   //LCD_Update(NULL);

   LCD_WriteString("hello");

    while(loop()){
        
        switch(BUTTON_GetButtonsEvents()){

            case BUTTON_L:
                LCD_WriteString("BUTTON_L");
                break;
            case BUTTON_F:
                LCD_WriteString("BUTTON_F");
                break;
            case BUTTON_R:
                LCD_WriteString("BUTTON_R");
                break;   
            case BUTTON_S:
                LCD_WriteString("BUTTON_S");
                break;
        }
    }

   LCD_Close(); 

return 0;
}
