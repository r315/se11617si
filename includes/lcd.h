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
#define YELLOW 0xFFE4
#define BLACK 0
#define PINK (RED|BLUE)
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
 * @param	c		: character to print.
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
* @param base : base a qual o numero deve de ser representado Ex:(2,10,16)
*             : bits 15-8 contem o numero minimo de digitos   Ex:(0:8, 1:08, 4:0123, 8:00001234)
**/
void LCD_WriteInt(uint32_t value, uint32_t base);

/**
 * @brief abre uma janela para estrita de dados.
 * */
void LCD_Window(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

/**
 * @brief Retorna a largura de um caractere em pixeis
 **/
uint8_t LCD_GetFontWidth(void);

/**
 * @brief Retorna a altura de um caractere em pixeis
 **/
uint8_t LCD_GetFontHeight(void);

/**
 * @brief Escreve size pixeis com cores indexados, é usada para desenhar sprites
 *        onde data uma tabela de cores e uma sequencia de cores a usar
 **/
void LCD_IndexedColor(uint16_t *colors, uint8_t *index, uint32_t size);
#endif

