#ifndef _space_h_
#define _space_h_

#define SCREEN_W LCD_W
#define SCREEN_H LCD_H

#define SPRITE_H 8
#define SPRITE_W 16
#define SPRITE_SIZE (SPRITE_W * SPRITE_H)

#define BGCOLOR BLACK

#define ON 1
#define OFF 0

#define MAX_PROJECTILES 5


void popSpace(void *ptr);
void space(int b);


#endif
