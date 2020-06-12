#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include "SDL/SDL.h"

//It is used to define a sprite
typedef struct Sprite_t{
    SDL_Surface* bmp;//what will be shown in the screen
    SDL_Rect rect;//coordinates and size of the surface
    int enabled; //if the button is enabled
    int (*onClick)(struct Sprite_t *, int *, char *); //pointer to a function that the button will execute when clicked
}Sprite_t;


#endif // SPRITE_H_INCLUDED
