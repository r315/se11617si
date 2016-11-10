#include <stdio.h> 
#include <display.h>


void LCD_Close(void);

int main(void){

   LCD_Init();
   
   LCD_Pixel(10,10,RED);
   
   getchar();
   
   LCD_Close;

return 0;
}
