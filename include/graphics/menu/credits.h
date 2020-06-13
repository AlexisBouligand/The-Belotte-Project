#ifndef CREDITS_H_INCLUDED
#define CREDITS_H_INCLUDED

#include <SDL/SDL.h>
#include "graphics/button.h"


/*Function that initialize the Credits section of the menu.
  It creates buttons, sprites and text needed for this section.

  Arguments description:
  - screen : the screen that will show the graphical game
  - buttons : dynamic array of buttons that will contain buttons of this section*/
void initCredits(SDL_Surface *screen, Array_of_buttons_t *buttons);

#endif
