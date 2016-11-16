/**
* @file		lab5.c
* @brief	Contains the graphic LCD API (parcial).
*     		It is intended to be used in ISO C conforming development
*     		environments and checks for this insofar as it is possible
*     		to do so.
* @version	1.0
* @date		10 Out. 2015
* @author	PSampaio
*
* Copyright(C) 2015, PSampaio
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

extern const unsigned char font8x16[97][16];

/**********************************************************************
 * !!! VERIFICAR OS TEMPOS ESPECIFICADOS NO MANUAL DO CONTROLADOR !!!
 **********************************************************************/

/**
 * @brief	Initilize LCD.
 * @return	Nothing
 */ 
void LCD_Init(void) {
	LCD_LowLevelInit();		// Low level initializations

	SPI_BeginTransfer(LCD_CS);

	LCD_Command(DISCTL); 	// display control
	LCD_Data(0x0C);
	LCD_Data(0x20);
	LCD_Data(0x0C);

	LCD_Command(COMSCN); 	// common scanning direction
	LCD_Data(0x01);

	LCD_Command(OSCON); 	// internal oscialltor on

	LCD_Command(SLPOUT); 	// sleep out

	LCD_Command(PWRCTR); 	// power ctrl
	LCD_Data(0x0F); 		//everything on, no external reference resistors

    LCD_Command(0xA7); 		// invert display

	LCD_Command(DATCTL); 	// data control
	LCD_Data(0x00); 		// 3 correct for normal sin7
	LCD_Data(0x00); 		// normal RGB arrangement
	LCD_Data(0x04); 		// 16-bit Grayscale Type A

	LCD_Command(VOLCTR); 	// electronic volume, this is the contrast/brightness
	LCD_Data(0x27); 		// volume (contrast) setting - fine tuning, original
	LCD_Data(0x03); 		// internal resistor ratio - coarse adjustment

	LCD_Command(DISON); 	// display on

	SPI_EndTransfer(LCD_CS);
}


/**
 * @brief	Write a character with specified color.
 * @param	x		: Column position.
 * @param	y		: Row position.
 * @param	fColor	: Foreground color.
 * @param	bColor	: Background color.
 * @return	Nothing
 */
void LCD_PutChar(char c, int x, int y, int fColor, int bColor) {
	int i, colIndex;
	unsigned int nCols;
	unsigned int nRows;
	unsigned int nBytes;
	unsigned char pixelRow;
	unsigned int pixel1, pixel2;
	unsigned char *pFont;
	unsigned char *pChar;

	SPI_BeginTransfer(LCD_CS);

	pFont = (unsigned char *) font8x16;
	nCols = *pFont;
	nRows = *(pFont + 1);
	nBytes = *(pFont + 2);

	pChar = pFont + (nBytes * (c - 0x1F)) + nBytes - 1;
	LCD_Command(PASET);
	LCD_Data(LCD_HEIGHT - (y + nRows - 1));
	LCD_Data(LCD_HEIGHT - (y));

	LCD_Command(CASET);
	LCD_Data(LCD_WIDTH - (x + nCols - 1));
	LCD_Data(LCD_WIDTH - (x));

	LCD_Command(RAMWR);

	for (i = 0; i < nBytes; i++) {
		pixelRow = *pChar--;
		for (colIndex = 0; colIndex < nCols / 2; colIndex++) {
			pixel1 = ((pixelRow & 0x1) != 0) ? fColor : bColor;
			pixelRow >>= 1;
			pixel2 = ((pixelRow & 0x1) != 0) ? fColor : bColor;
			pixelRow >>= 1;
			LCD_Data((pixel1 >> 4) & 0xFF);
			LCD_Data(((pixel1 & 0xF) << 4) | ((pixel2 >> 8) & 0xF));
			LCD_Data(pixel2 & 0xFF);
		}
	}
	SPI_EndTransfer(LCD_CS);
}


