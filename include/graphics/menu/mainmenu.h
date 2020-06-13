#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <SDL/SDL.h>
#include "graphics/button.h"


/*Function used to return to the mainmenu section
  This function is a function executed when we click a button.

  It's arguments are needed to be compatible with the function pointer of Sprite_t
  but are unused here.

  This function returns 0, value corresponding to the Main menu section*/
int returnToMenu(Sprite_t *button, int *iargs, char *cargs);


/*Function that initialize the Main menu section of the menu.
  It creates buttons, sprites and text needed for this section.

  Arguments description:
  - screen : the screen that will show the graphical game
  - buttons : dynamic array of buttons that will contain buttons of this section*/
void initMenu(SDL_Surface *screen, Array_of_buttons_t *buttons);

#endif
