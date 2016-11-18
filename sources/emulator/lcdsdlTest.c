#include <stdio.h> 
#include <lcd.h>
#include "lcdsdl.h"

int main(void){

   LCD_Init();
   
  // LCD_Pixel(10,10,RED);
   LCD_OpenFrame(0,0,LCD_W,LCD_H);
   LCD_Fill(BLUE,LCD_SIZE);
   LCD_Update();
   getchar();
   
   LCD_Close();

return 0;
}
