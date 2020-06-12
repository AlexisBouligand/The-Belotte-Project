#include <SDL/SDL_ttf.h>
#include "graphics/menu/credits.h"
#include "graphics/menu/mainmenu.h"
#include "graphics/SDLCheck.h"

void initCredits(SDL_Surface *screen, Array_of_buttons_t *buttons)
{
  char *text[] = {"Bouligand Alexis", "Dewasmes Oscar", "Giacinti Louis"}; //credits names
  int i;

  TTF_Font *font_title = TTF_OpenFont("assets/font/Minecraft.ttf", 65); //creating font with a size of 65
  checkFont(font_title);
  TTF_SetFontStyle(font_title, TTF_STYLE_BOLD); //set to bold

  TTF_Font *font_names = TTF_OpenFont("assets/font/Minecraft.ttf", 50);
  checkFont(font_names);
  SDL_Color color = {99, 92, 92};

  buttons->b = malloc(5 * sizeof(Sprite_t));
  buttons->length = 5;

  createButton(&(buttons->b[0]), 0, screen->h * 0.02, TTF_RenderText_Blended(font_title, "Credits :", color), NULL); //creating The title (button that do not trigger anything)
  SDL_BlitSurface(buttons->b[0].bmp, NULL, screen, &(buttons->b[0].rect)); //updating the text to initialize rect.w and rect.h
  buttons->b[0].rect.x = screen->w / 2 - buttons->b[0].rect.w / 2; //setting the text in the middle

  for(i = 1; i < 4; i++) //create text sprite for each name
  {
    createButton(&(buttons->b[i]), 0, (i+1) * screen->h * 0.12, TTF_RenderText_Blended(font_names, text[i-1], color), NULL);
    SDL_BlitSurface(buttons->b[i].bmp, NULL, screen, &(buttons->b[i].rect));
    buttons->b[i].rect.x = screen->w / 2 - buttons->b[i].rect.w / 2;
  }

  createButton(&(buttons->b[4]), screen->w / 2 - 225 / 2, screen->h * 0.6, SDL_LoadBMP("assets/sprite/button/menu_button4.bmp"), returnToMenu); //button to return to main menu

  TTF_CloseFont(font_title); //closing the font
  TTF_CloseFont(font_names);
}
