/**
* @file		ili9341.h
* @brief	Contains the ILI9341 lcd controller API headers and symbols.
*     		
* @version	1.0
* @date		5 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _ili9341_h_
#define _ili9341_h_

#include <stdint.h>
#include <lpc2106.h>
#include <gpio.h>

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
 
#define LCD_CS   3
#define LCD_RS   9
#define LCD_RST 10
#define LCD_BKL  8

#define LCD_CS0  GPIO_Clr(LCD_CS)
#define LCD_CS1  GPIO_Set(LCD_CS)
#define LCD_RS0  GPIO_Clr(LCD_RS)
#define LCD_RS1  GPIO_Set(LCD_RS)
#define LCD_RST0 GPIO_Clr(LCD_RST)
#define LCD_RST1 GPIO_Set(LCD_RST)
#define LCD_BKL0 GPIO_Clr(LCD_BKL)
#define LCD_BKL1 GPIO_Set(LCD_BKL)

#define LCD_PIN_INIT					\
            GPIO_SetOutput(LCD_CS); 	\
            GPIO_SetOutput(LCD_RS);		\
            GPIO_SetOutput(LCD_RST);	\
            GPIO_SetOutput(LCD_BKL);	\

#define SWRST   0x01
#define RDDID   0x04
#define SLPIN   0x10
#define SLPOUT  0x11
#define DISPOFF 0x28
#define DISPON  0x29
#define CASET   0x2A
#define PASET   0x2B
#define RAMWR   0x2C
#define MAC     0x36	// Memory Access Control 
#define COLMOD  0x3A // Pixel Format set
#define FRCONN  0xB1	// Frame rate control Normal mode
#define FRCONI  0xB2	// Frame rate control Idle mode
#define FRCONP  0xB3	// Frame rate control Partial mode
#define DFCTL   0xB6 // Display Function Control 
#define PCON1   0xC0	// power control 1
#define PCON2   0xC1	// power control 2
#define VCOM1   0xC5	// VCOM control 1
#define VCOM2   0xC7	// VCOM control 2
#define PCONA   0xCB	// Power Control A
#define PCONB   0xCF	// Power Control B
#define DTCONA  0xE8 // Driver Timming Control A
#define DTCONB  0xEA // Driver Timming Control B
#define PSCON   0xED // Power on Sequence control
#define PRCON   0xF7	// Pump ratio control


/**
* @brief Opens a frame for writing data, data can be send immediately
*        after this call
**/
void LCD_OpenFrame(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

/**
* @brief Fills n pixels with the same color
*         Note: LCD_OpenFrame must be called 
*				setting a frame os n pixels
**/
void LCD_Fill(uint16_t color, uint32_t n);

/**
* @brief
**/
void LCD_Data16(uint16_t data);

#endif

