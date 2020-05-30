#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include "SDL/SDL.h"

//It is used to define a sprite
typedef struct Sprite_t{
    SDL_Surface* bmp;
    SDL_Rect rect;
}Sprite_t;


#endif // SPRITE_H_INCLUDED
