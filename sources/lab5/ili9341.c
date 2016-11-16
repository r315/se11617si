#include <spi.h>
#include <timer.h>
#include <display.h>
#include "ili9341.h"

#ifndef SPI_16
void data8(uint16_t data){	
    RS1;
    CS0;
    SPI_Send(data);	
    CS1;	
}

void data16(uint16_t data){	
    RS1;
    CS0;
    SPI_Send(data>>8);
    SPI_Send(data);
    CS1;
}

void LCD_Fill(uint16_t data, uint32_t n){
    RS1;
    CS0;
    while(n--){		
        SPI_Send(data>>8);
        SPI_Send(data);
    }
    CS1;
}
void command(uint16_t data){
    RS0;
    CS0;
    SPI_Send(data);
    CS1;	
}

void LCD_OpenWrap(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
   command(CASET);  
   data16(x1);   
   data16(x2);
  
   command(PASET);
   data16(y1);
   data16(y2);

   command(RAMWR);         				 
}

void LCD_Init(void){

        LCD_PIN_INIT;

        RST0;
        TIMER0_DelayMs(10);
        RST1;
  
        command(PCONA);  
        data8(0x39); 
        data8(0x2C); 
        data8(0x00); 
        data8(0x34); 
        data8(0x02); 

        command(PCONB);  
        data8(0x00); 
        data8(0XC1); 
        data8(0X30); 

        command(DTCONA);  
        data8(0x85); 
        data8(0x00); 
        data8(0x78); 

        command(DTCONB);  
        data8(0x00); 
        data8(0x00); 
 
        command(PSCON);  
        data8(0x64); 
        data8(0x03); 
        data8(0X12); 
        data8(0X81); 

        command(PRCON);  
        data8(0x20); 
  
        command(PCON1);    //Power control 
        data8(0x23);   //VRH[5:0] 
 
        command(PCON2);    //Power control 
        data8(0x10);   //SAP[2:0];BT[3:0] 

        command(VCOM1);    //VCM control 
        data8(0x3e);   //Contrast
        data8(0x28); 
 
        command(VCOM2);    //VCM control2 
        data8(0x86);   //--
 
        command(MAC);    // Memory Access Control 
        data8(0x48);  //C8	   //48 68??//28 E8 ??

        command(COLMOD);    
        data8(0x55);   //16bit/pixel

        command(FRCONN);    
        data8(0x00);  
        data8(0x18); 
 
        command(DFCTL);    // Display Function Control 
        data8(0x08); 
        data8(0x82);
        data8(0x27);  

        command(SLPOUT);    //Exit Sleep 
        TIMER0_DelayMs(120); 
                
        command(DISPON);    //Display on 
        command(RAMWR);  

        BKL1; 
}
#else

void data16(uint16_t data){	
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


void command(uint16_t data){
    RS0;
    CS0;
    SPI_Send(data);
    CS1;	
}

void LCD_OpenWrap(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
   command(CASET);
   data16(x1);
   data16(x2);
  
   command(PASET);
   data16(y1);
   data16(y2);
   command(RAMWR);         				 
}

void LCD_Init(void){

        PIN_INIT;

        RST0;
        TIMER0_DelayMs(10);
        RST1;
  
        command(PCONA);  
        data16(0x39); 
        data16(0x2C); 
        data16(0x00); 
        data16(0x34); 
        data16(0x02); 

        command(PCONB);  
        data16(0x00); 
        data16(0XC1); 
        data16(0X30); 

        command(DTCONA);  
        data16(0x85); 
        data16(0x00); 
        data16(0x78); 

        command(DTCONB);  
        data16(0x00); 
        data16(0x00); 
 
        command(PSCON);  
        data16(0x64); 
        data16(0x03); 
        data16(0X12); 
        data16(0X81); 

        command(PRCON);  
        data16(0x20); 
  
        command(PCON1);    //Power control 
        data16(0x23);   //VRH[5:0] 
 
        command(PCON2);    //Power control 
        data16(0x10);   //SAP[2:0];BT[3:0] 

        command(VCOM1);    //VCM control 
        data16(0x3e);   //Contrast
        data16(0x28); 
 
        command(VCOM2);    //VCM control2 
        data16(0x86);   //--
 
        command(MAC);    // Memory Access Control 
        data16(0x48);  //C8	   //48 68??//28 E8 ??

        command(COLMOD);    
        data16(0x55);   //16bit/pixel

        command(FRCONN);    
        data16(0x00);  
        data16(0x18); 
 
        command(DFCTL);    // Display Function Control 
        data16(0x08); 
        data16(0x82);
        data16(0x27);  

        command(SLPOUT);    //Exit Sleep 
        TIMER0_DelayMs(120); 
                
        command(DISPON);    //Display on 
        command(RAMWR);  

        BKL1; 
}
#endif
void LCD_Bkl(uint32_t state){
    if(state) BKL1;
    else	BKL0;
}

 
