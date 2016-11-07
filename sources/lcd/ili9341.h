/**
* @file		ili9341.h
* @brief	Contains the ILI9341 API and symbols.
*     		
* @version	1.0
* @date		5 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _ili9341_h_
#define _ili9341_h_

#include <stdint.h>
#include <lpc2106.h>

/**
* @brief Lcd Pin configuration:
*		P0.3  CS
*		P0.4  SCK
*		P0.5  SO
*       P0.6  SI      
*		P0.8  Backlight enable
*		P0.9  C'/D
*		p0.10 RST
**/
 
#define LCD_CS (1<<3)  //
#define LCD_RS (1<<9)  //
#define LCD_RST (1<<10) //
#define LCD_BKL (1<<8)

#define CS0  GPIO0->CLR = LCD_CS
#define CS1  GPIO0->SET = LCD_CS
#define RS0  GPIO0->CLR = LCD_RS
#define RS1  GPIO0->SET = LCD_RS
#define RST0 GPIO0->CLR = LCD_RST
#define RST1 GPIO0->SET = LCD_RST
#define BKL0 GPIO0->CLR = LCD_BKL
#define BKL1 GPIO0->SET = LCD_BKL

#define PIN_INIT	GPIO0->DIR |= LCD_CS | LCD_RS | LCD_RST | LCD_BKL 

#define RDDID 0x04
#define SLPIN  0x10
#define SLPOUT 0x11
#define DISPON 0x29
#define CASET 0x2A
#define PASET 0x2B
#define RAMWR 0x2C
#define MAC 0x36	// Memory Access Control 
#define COLMOD 0x3A // Pixel Format set
#define FRCONN 0xB1	// Frame rate control Normal mode
#define FRCONI 0xB2	// Frame rate control Idle mode
#define FRCONP 0xB3	// Frame rate control Partial mode
#define DFCTL 0xB6  // Display Function Control 
#define PCON1 0xC0	// power control 1
#define PCON2 0xC1	// power control 2
#define VCOM1 0xC5	// VCOM control 1
#define VCOM2 0xC7	// VCOM control 2
#define PCONA 0xCB	// Power Control A
#define PCONB 0xCF	// Power Control B
#define DTCONA 0xE8 // Driver Timming Control A
#define DTCONB 0xEA // Driver Timming Control B
#define PSCON 0xED  // Power on Sequence control
#define PRCON 0xF7	// Pump ratio control


void data16(uint16_t data);
void data8(uint8_t data);
void command(uint8_t data);

#endif

