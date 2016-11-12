/**
* @file		.h
* @brief	Contains the ... API header.
*     		
* @version	1.0
* @date		5 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _display_h_
#define _display_h_

#include <stdint.h>

/* basic color constants */
#define RGB(r,g,b)  (int)((r<<11) | (g<<5) | b)
#define RED (0x1F<<11)
#define GREEN (0x3F<<5)
#define BLUE 0x1f
#define BLACK 0
#define WHITE 0xFFFF

void LCD_Init(void);

void LCD_Bkl(uint32_t state);

void LCD_SetWrap(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

void LCD_Fill(uint16_t color, uint32_t n);

void LCD_Rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

void LCD_Data(uint16_t color);
#endif
