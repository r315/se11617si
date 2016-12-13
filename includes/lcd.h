/**
* @file		lcd.h
* @brief	Contains the LCD API header.
*     		
* @version	1.0
* @date		16 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _lcd_h_
#define _lcd_h_

#include <stdint.h>

#define LCD_W 240
#define LCD_H 320
#define LCD_SIZE LCD_W * LCD_H

/* basic color constants */
#define RGB(r,g,b)  (int)((r<<11) | (g<<5) | b)
#define RED (0x1F<<11)
#define GREEN (0x3F<<5)
#define BLUE 0x1f
#define BLACK 0
#define WHITE 0xFFFF
#define UBUNTU RGB(6,2,4)

/**
* @brief Função de inicialização do lcd
*			Nota: unica função retirada da api disponibilizada
*			pelo fabricante do controlador
**/
void LCD_Init(void);

/**
* @brief Escreve um carácter na posição corrente do cursor.
**/
void LCD_WriteChar(char ch);

/**
* @brief Escreve uma string na posição corrente do cursor.
**/
void LCD_WriteString(char *str);

/**
* @brief Configura as cores a usar nos caracteres
**/
void LCD_SetColors(uint32_t _fColor, uint32_t _bColor);

/**
* @brief Posiciona o cursor na linha y e coluna x do mostrador.
**/
void LCD_Goto(int x, int y);

/**
* @brief Posiciona o cursor na linha seguinte
**/
void LCD_NewLine(void);


/**
* @brief Limpa o visor com a cor especificada.
**/
void LCD_Clear(int color);

/**
* @brief controla a luz de fundo do lcd
**/
void LCD_Bkl(uint32_t state);

/**
 * @brief	Write a character with specified color.
 * @param	x		: Column position.
 * @param	y		: Row position.
 * @param	fColor	: Foreground color.
 * @param	bColor	: Background color.
 * @return	Nothing
 */
void LCD_PutChar(char c, int x, int y, int fColor, int bColor);

/**
* @brief Mostra um inteiro no lcd
* @param value : valor a mostrar
* @param base : base a qual o numero deve de ser representado
*             : bits 15-8 contem o numero minimo de digitos
**/
void LCD_WriteInt(uint32_t value, uint32_t base);

#endif

