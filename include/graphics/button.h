#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include "graphics/sprite.h"

typedef struct //dynamic array containing buttons
{
  int length; //length of the array
  Sprite_t *b; //pointer to the memory location
} Array_of_buttons_t;

//Ask for a Sprite_t(for the coordinates) and for the mouse cursor coordinates
//function that checks if the mouse is on a button
//Return 0 or 1(boolean)
int checkMouseCoordinates(Sprite_t button, int mouse_x, int mouse_y); 

//Ask for an array of sprite(menu or hand card typically)
//The cards buttons
//Return the button case on which the mouse have clicked. Useful to use with a switch
//Return -1 if there is nothing useful to return
int buttonPressed(Sprite_t *button, int size_of_button_array);

//Ask for all the components of a button(a Sprite_t, cooribnates, a SDL_surfacea, a function pointer)
//Function that create a button
void createButton(Sprite_t *button, int x, int y, SDL_Surface *surface, int (*onClick)(Sprite_t *, int *, char *));

#endif // BUTTON_H_INCLUDED
