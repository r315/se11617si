#include <spi.h>
#include <timer.h>
//#include <lcd.h>
#include "ili9341.h"


void LCD_Bkl(uint32_t state){
    if(state) BKL1;
    else	BKL0;
}

void LCD_Data8(uint16_t data){	
    RS1;
    CS0;
    SPI_Send(data);	
    CS1;	
}

void LCD_Data16(uint16_t data){	
    RS1;
    CS0;
    SPI_Send(data);
    CS1;
}

void LCD_Fill(uint16_t data, uint32_t n){
    RS1;
    CS0;
    while(n--)        
        SPI_Send(data);
    CS1;
}

void LCD_Command(uint16_t data){
    RS0;
    CS0;
    SPI_Send(data);
    CS1;	
}

void LCD_OpenFrame(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
   LCD_Command(CASET);  
   LCD_Data16(x);   
   LCD_Data16(x + w -1);
  
   LCD_Command(PASET);
   LCD_Data16(y);
   LCD_Data16(y + h - 1);

   LCD_Command(RAMWR);         				 
}

void LCD_Init(void){

        LCD_PIN_INIT;

        RST0;
        TIMER0_DelayMs(10);
        RST1;
  
        LCD_Command(PCONA);  
        LCD_Data8(0x39); 
        LCD_Data8(0x2C); 
        LCD_Data8(0x00); 
        LCD_Data8(0x34); 
        LCD_Data8(0x02); 

        LCD_Command(PCONB);  
        LCD_Data8(0x00); 
        LCD_Data8(0XC1); 
        LCD_Data8(0X30); 

        LCD_Command(DTCONA);  
        LCD_Data8(0x85); 
        LCD_Data8(0x00); 
        LCD_Data8(0x78); 

        LCD_Command(DTCONB);  
        LCD_Data8(0x00); 
        LCD_Data8(0x00); 
 
        LCD_Command(PSCON);  
        LCD_Data8(0x64); 
        LCD_Data8(0x03); 
        LCD_Data8(0X12); 
        LCD_Data8(0X81); 

        LCD_Command(PRCON);  
        LCD_Data8(0x20); 
  
        LCD_Command(PCON1);    //Power control 
        LCD_Data8(0x23);   //VRH[5:0] 
 
        LCD_Command(PCON2);    //Power control 
        LCD_Data8(0x10);   //SAP[2:0];BT[3:0] 

        LCD_Command(VCOM1);    //VCM control 
        LCD_Data8(0x3e);   //Contrast
        LCD_Data8(0x28); 
 
        LCD_Command(VCOM2);    //VCM control2 
        LCD_Data8(0x86);   //--
 
        LCD_Command(MAC);    // Memory Access Control 
        LCD_Data8(0x48);  //C8	   //48 68??//28 E8 ??

        LCD_Command(COLMOD);    
        LCD_Data8(0x55);   //16bit/pixel

        LCD_Command(FRCONN);    
        LCD_Data8(0x00);  
        LCD_Data8(0x18); 
 
        LCD_Command(DFCTL);    // Display Function Control 
        LCD_Data8(0x08); 
        LCD_Data8(0x82);
        LCD_Data8(0x27);  

        LCD_Command(SLPOUT);    //Exit Sleep 
        TIMER0_DelayMs(120); 
                
        LCD_Command(DISPON);    //Display on 
        LCD_Command(RAMWR);  

        BKL1; 
}

 
