#ifndef SDLCHECK_H_INCLUDED
#define SDLCHECK_H_INCLUDED
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "graphics/sprite.h"
#include "game/variableManagement.h"
//Display a potential error in stderr
//Need a surface pointer
void checkError(SDL_Surface *surface);
//Need a font pointer
void checkFont(TTF_Font *font);

//Free the surface when they are not needed
//Need an array of sprite_t (=button) and the size of this array
void freeButtonSurface(Sprite_t *button, int array_size);

void freeCardSurface(Card_t *cards, int array_size);
//Need an array of Card_t and the size of this array
#endif // SDLCheck_H_INCLUDED
