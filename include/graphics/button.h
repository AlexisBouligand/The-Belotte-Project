#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include "graphics/sprite.h"

typedef struct //dynamic array containing buttons
{
  int length; //length of the array
  Sprite_t *b; //pointer to the memory location
} Array_of_buttons_t;

int checkMouseCoordinates(Sprite_t button, int mouse_x, int mouse_y); //function that checks if the mouse is on a button

//Ask for an array of sprite(menu or hand card typically)
//Return the button case on which the mouse have clicked. Useful to use with a switch
//Return -1 if there is nothing useful to return
int buttonPressed(Sprite_t *button, int size_of_button_array);

//function that create a button
void createButton(Sprite_t *button, int x, int y, SDL_Surface *surface, int (*onClick)(Sprite_t *, int *, char *));

#endif // BUTTON_H_INCLUDED
