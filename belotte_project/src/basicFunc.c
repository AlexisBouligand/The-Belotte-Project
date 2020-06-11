#include <stdio.h>
#include <stdlib.h>
#include "../include/basicFunc.h"


//Needed to check the errors

void checkError(SDL_Surface *surface)
{
    if(surface == NULL)
    {
        fprintf(stderr,"Error when initializing the surface\n%s\n", SDL_GetError());
    }
}

void checkFont(TTF_Font *font)
{
      if(font == NULL)
    {
        fprintf(stderr,"Error when initializing the surface\n%s\n", TTF_GetError());
    }
}

void freeButtonSurface(Sprite_t *button, int array_size)
{
    for(int i = 0 ; i<array_size ; i++)
    {
        SDL_FreeSurface(button[i].bmp);
    }
}


void freeCardSurface(Card_t *cards)
{
    for(int i = 0 ;i <32 ; i++)
    {
        SDL_FreeSurface(cards[i].card_sprite.bmp);
    }
}
