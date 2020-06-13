#ifndef START_H_INCLUDED
#define START_H_INCLUDED

#include <SDL/SDL.h>
#include "graphics/button.h"

/*Function that initialize the Start section of the menu.
  It creates buttons, sprites and text needed for this section.

  Arguments description:
  - screen : the screen that will show the graphical game
  - buttons : dynamic array of buttons that will contain buttons of this section*/
void initStart(SDL_Surface *screen, Array_of_buttons_t *buttons);

/*Function triggered in the loop of the section.
  It gets keyboard's input and write it to the screen to get the name of the player.
  It also checks if we clicked on any button.

  Arguments description:
  - screen : the screen that will show the graphical game
  - buttons : dynamic array of buttons that contains each button of this section
  - event : SDL_Event used to get keyboard input and mouse input
  - name : pointer to a string containing the name of the player

  This functions return 0 if we clicked on the button to return to the menu or 5 if we want the game loop to start*/
int getButtonAndKeysEvent(SDL_Surface *screen, Array_of_buttons_t *buttons, SDL_Event event, char *name);
#endif
