#ifndef _space_h_
#define _space_h_

#define SCREEN_W 128
#define SCREEN_H 128

#define SCREEN_SX (LCD_W/2) - (SCREEN_W/2)
#define SCREEN_SY (LCD_H/2) - (SCREEN_H/2)

#define SPRITE_H 8
#define SPRITE_W 16
#define SPRITE_SIZE (SPRITE_W * SPRITE_H)

#define BGCOLOR BLACK

#define ON 1
#define OFF 0

#define MAX_PROJECTILES 5
#define MAX_ALIENS 6*6
#define SPRITES_DATA spcinv
#define TANK_DATA SPRITES_DATA + (SPRITE_SIZE * 6)


void popSpace(void *ptr);
void space(int b);


#endif
