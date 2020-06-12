#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <SDL/SDL.h>
#include "graphics/button.h"

int returnToMenu(Sprite_t *button, int *iargs, char *cargs); //function that return section's number corresponding to the menu

void initMenu(SDL_Surface *screen, Array_of_buttons_t *buttons); //function that initialize the main menu section

#endif
