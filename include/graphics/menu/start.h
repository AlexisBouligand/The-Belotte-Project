#ifndef START_H_INCLUDED
#define START_H_INCLUDED

#include <SDL/SDL.h>
#include "graphics/button.h"

void initStart(SDL_Surface *screen, Array_of_buttons_t *buttons); //function to initialiaze the start section

int getButtonAndKeysEvent(SDL_Surface *screen, Array_of_buttons_t *buttons, SDL_Event event, char *name); //function that checks what the user type on his keyboard and check buttons

#endif
