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

#define SPEED 5

#define MAX_PROJECTILES 1
#define MAX_ALIENS 6*6
#define SPRITES_DATA spcinv
#define TANK_DATA SPRITES_DATA + (SPRITE_SIZE * 6)

#define PROJECTILE_W 2
#define PROJECTILE_H 6

typedef struct _sprite{
    int x;
    int y;
    uint8_t type;
    uint8_t *data;
    uint8_t alive;
}Sprite;

typedef struct projectile{
    int x;
    int y;
    uint16_t color;
    uint8_t inmotion;
}Projectile;

typedef struct _gameData{
    uint32_t score;
    uint8_t state;
    Sprite tank;
    Sprite aliens[MAX_ALIENS];
    Projectile tankprojectiles[MAX_PROJECTILES];
    Projectile alienprojectiles[MAX_PROJECTILES];
}GameData;

void popSpace(void *ptr);
void space(int b);
void newGame(GameData *gd);

#endif
