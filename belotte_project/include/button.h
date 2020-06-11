#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include "../include/sprite.h"

//Ask for an array of sprite(menu or hand card typically)
//Return the button case on which the mouse have clicked. Useful to use with a switch
//Return -1 if there is nothing useful to return
int buttonPressed(Sprite_t *button, int size_of_button_array);

#endif // BUTTON_H_INCLUDED
