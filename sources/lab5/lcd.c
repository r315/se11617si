#include <spi.h>
#include <lcd.h>
#include "ili9341.h"

extern const unsigned char font8x16[97][16];
static uint32_t _x, _y;
static uint32_t _fColor, _bColor;

void LCD_SetColors(uint32_t fColor, uint32_t bColor){
	_fColor = fColor;
	_bColor = bColor;
}


void LCD_WriteInt(uint32_t value, uint32_t base){
uint8_t digits[32];        //maximo de 32 digitos 
uint8_t padding = base>>8;
uint8_t digit, count;
	
	if(!value){                    // se valor for zero
        while(padding--)           // apenas se mosta um digito zero
    		LCD_WriteChar('0');    // ou os especificados por padding
		return;
	}

    count = 0;
    base &= 0xFF;

	while(value){
		digit = value % base;       // obter o digito das unidades
        if(digit > 9)             // se o valor for superior a 9
            digit += ('A'-('9'+1)); // o offset para tabela ascii tem de ser ajustado
        digit += '0';
        digits[count++] = digit;    // guarda o digito e increnenta o contador de digitos
        value = value/base;         // passa para o proximo digito
	}

    padding = (padding > count) ? padding-count : 0;  //verifica o numero minimo de digitos a mostrar

    while(padding--){
        LCD_WriteChar('0');
    }

    while(count--){
        LCD_WriteChar(digits[count]);
    }

}

void LCD_WriteChar(char ch){
	if(ch == '\n')
        LCD_NewLine();
    else
	    LCD_PutChar(ch, _x, _y, _fColor, _bColor);
}

void LCD_WriteString(char *str){
	while(*str)
		LCD_WriteChar(*str++);
}

void LCD_Goto(int x, int y){
		_x = x;
		_y = y;
}

void LCD_NewLine(void){
uint8_t h = *((uint8_t*)font8x16+1);
    _y += h;
    if(_y > (LCD_H - h))
        _y = 0;
    _x = 0;
}

void LCD_Clear(int color){
	LCD_Window(0,0,LCD_W,LCD_H);	
	LCD_Fill(color, LCD_SIZE);	
}

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
		
/*
	pChar = pFont + (nBytes * (c - 0x1F)) + nBytes - 1;
	LCD_Command(PASET);
	LCD_Data(LCD_H - (y + nRows - 1));
	LCD_Data(LCD_H - (y));

	LCD_Command(CASET);
	LCD_Data(LCD_W - (x + nCols - 1));
	LCD_Data(LCD_W - (x));
*/

	pChar = pFont + (nBytes * (c - 0x1F));
	
	_x = (x + nCols);
	_y = y;
	_fColor = fColor;
	_bColor = bColor;

	if( _x >= LCD_W){
		_x = 0;
		_y += nRows;
		if(_y >= LCD_H)
			_y = 0;
	}	
	
	LCD_Window(x,y,nCols,nRows);

	//LCD_Command(RAMWR);

	for (i = 0; i < nBytes; i++) {
		pixelRow = *pChar++;
//		pixelRow = *pChar--;
//		for (colIndex = 0; colIndex < nCols / 2; colIndex++) {
		for (colIndex = 0; colIndex < nCols; colIndex++) {
			LCD_Data(((pixelRow & 0x80) != 0) ? fColor : bColor);
			pixelRow <<= 1;
			/*pixel1 = ((pixelRow & 0x1) != 0) ? fColor : bColor;
			pixelRow >>= 1;
			pixel2 = ((pixelRow & 0x1) != 0) ? fColor : bColor;
			pixelRow >>= 1;
			LCD_Data((pixel1 >> 4) & 0xFF);
			LCD_Data(((pixel1 & 0xF) << 4) | ((pixel2 >> 8) & 0xF));
			LCD_Data(pixel2 & 0xFF);*/
			
		}
	}
	SPI_EndTransfer(LCD_CS);	
}


