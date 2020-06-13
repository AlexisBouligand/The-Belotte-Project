#include <SDL/SDL_ttf.h>
#include "graphics/menu/mainmenu.h"
#include "graphics/SDLCheck.h"


int returnToMenu(Sprite_t *button, int *iargs, char *cargs)
{
  return 0;
}

/*Function that return the number corresponding of the button's section

  Arguments description:
  - button : the clicked button (unused but necessary because of the function pointer)
  - iargs : number of the section
  - cargs : unused*/
int getSection(Sprite_t *button, int *iargs, char *cargs)
{
  return *iargs; //section position in init_functions and loop_functions
}

void initMenu(SDL_Surface *screen, Array_of_buttons_t *buttons)
{
  int i; //counter
  char file_str[] = "assets/sprite/button/menu_button0.bmp"; //string that contain the button's image path

  TTF_Font *font = TTF_OpenFont("assets/font/Minecraft.ttf", 65); //font and size of the text
  checkFont(font);

  TTF_SetFontStyle(font, TTF_STYLE_BOLD); //set to bold
  SDL_Color color = {99, 92, 92}; //color of the font

  buttons->b = malloc(5 * sizeof(Sprite_t)); //allocating memory for 5 buttons
  buttons->length = 5; //setting length

  createButton(&(buttons->b[0]), 0, screen->h * 0.02, TTF_RenderText_Blended(font, "Coinche Game", color), NULL); //creating The title (button that do not trigger anything)
  SDL_BlitSurface(buttons->b[0].bmp, NULL, screen, &(buttons->b[0].rect)); //updating the text to initialize rect.w and rect.h
  buttons->b[0].rect.x = screen -> w/2 - buttons->b[0].rect.w / 2; //setting the text in the middle

  for(i = 1; i < 5; i++)
  {
    file_str[32] = i + 48; //setting the menu_button number to the one needed
    //creating buttons with the corrseponding image
    createButton(&(buttons->b[i]), screen->w / 2 - 225 / 2, (i+1) * screen->h * 0.12, SDL_LoadBMP(file_str), getSection);
  }
  TTF_CloseFont(font); //closing the font
}
