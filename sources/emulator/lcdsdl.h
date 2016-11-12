#ifndef _lcdsdl_h_
#define _lcdsdl_h_

/* lcd constants */
#define LCD_W 128
#define LCD_H 128
#define LCD_SIZE (uint32_t)(LCD_W * LCD_H)

static const char windowTitle[] = {"lcd emulator"};

void LCD_Close(void);
void LCD_Update(void);

#endif
