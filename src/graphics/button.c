#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "graphics/button.h"
#include "graphics/sprite.h"
#include "graphics/SDLCheck.h"

int checkMouseCoordinates(Sprite_t button, int mouse_x, int mouse_y)
{
  return (mouse_x >= button.rect.x && mouse_x <= button.rect.x + button.rect.w
          && mouse_y >= button.rect.y && mouse_y <= button.rect.y + button.rect.h);
}


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
                    if(checkMouseCoordinates(button[i], event.button.x, event.button.y))
                    {

                        variable_to_return = i;


                    }
                }
            }
        }

        return variable_to_return;

}

void createButton(Sprite_t *button, int x, int y, SDL_Surface *surface, int (*onClick)(Sprite_t *, int *, char *))
{

  button->rect.x = x;
  button->rect.y = y;
  button->enabled = 1;
  button->bmp = surface;
  checkError(button->bmp);
  button->onClick = onClick;

}
