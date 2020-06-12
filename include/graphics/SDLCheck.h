#ifndef SDLCHECK_H_INCLUDED
#define SDLCHECK_H_INCLUDED
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "graphics/sprite.h"
#include "game/variableManagement.h"
//Display a potential error in stderr
void checkError(SDL_Surface *surface);
void checkFont(TTF_Font *font);
void freeButtonSurface(Sprite_t *button, int array_size);
void freeCardSurface(Card_t *cards, int array_size);

#endif // SDLCheck_H_INCLUDED
