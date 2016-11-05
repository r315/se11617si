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

/* lcd constants */
#define LCD_W 240
#define LCD_H 320
#define LCD_SIZE (uint32_t)(LCD_W * LCD_H)

/* basic color constants */
#define RGB(r,g,b)  (int)((r<<11) | (g<<5) | b)
#define RED (0x1F<<11)
#define GREEN (0x3F<<5)
#define BLUE 0x1f
#define BLACK 0
#define WHITE 0xFFFF

void LCD_Init(void);

void LCD_Bkl(uint32_t state);

void LCD_OpenWrap(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

void LCD_Fill(uint16_t data, uint32_t n);

#endif
