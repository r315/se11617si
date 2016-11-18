#ifndef _lcdsdl_h_
#define _lcdsdl_h_

static const char windowTitle[] = {"lcd emulator"};

void LCD_Close(void);
void LCD_Update(void);

void LCD_Data(uint16_t color);
void LCD_OpenFrame(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void LCD_Fill(uint16_t color, uint32_t n);

#endif
