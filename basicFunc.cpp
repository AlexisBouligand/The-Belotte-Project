#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

//Needed to check the errors

void checkError(SDL_Surface *surface)
{
    if(surface == NULL)
    {
        fprintf(stderr,"Error when initializing the surface\n%s\n", SDL_GetError());
    }
}



