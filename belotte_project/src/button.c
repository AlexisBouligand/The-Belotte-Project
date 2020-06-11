#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../include/../include/button.h"
#include "../include/sprite.h"


int buttonPressed(Sprite_t *button, int size_of_button_array)
{

    SDL_Event event;
    int variable_to_return = -1;

        SDL_WaitEvent(&event);
        //I use an If because there is only 1 event to check
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                for(int i = 0 ; i<size_of_button_array ; i++)
                {
                    //If the user click on the right zone
                    if((button[i].rect.x < event.button.x  &&  event.button.x < button[i].rect.x + button[i].bmp->w)   &&   (button[i].rect.y< event.button.y  &&  event.button.y < button[i].rect.y + button[i].bmp->h))
                    {

                        variable_to_return = i;


                    }
                }
            }
        }

        return variable_to_return;

}
