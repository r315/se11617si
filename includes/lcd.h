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
* @brief Posiciona o cursor na linha x e coluna y do mostrador.
**/
void LCD_Goto(int x, int y);
/**
* @brief Limpa o visor com a cor especificada.
**/
void LCD_Clear(int color);
#endif

