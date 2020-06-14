#include <SDL/SDL_ttf.h>
#include "menu/leader_file.h"
#include "graphics/menu/leaderboard.h"
#include "graphics/menu/mainmenu.h"
#include "graphics/SDLCheck.h"

void initLeader(SDL_Surface *screen, Array_of_buttons_t *buttons)
{
  int i;
  int best_players_number;

  TTF_Font *title_font = TTF_OpenFont("assets/font/Minecraft.ttf", 65); //using times.ttf font with a size of 65
  checkFont(title_font);
  TTF_SetFontStyle(title_font, TTF_STYLE_BOLD); //set to bold

  TTF_Font *text_font = TTF_OpenFont("assets/font/Minecraft.ttf", 50);
  checkFont(text_font);

  SDL_Color color = {99, 92, 92}; //color of the font

  char best_players[3][30]; //string array containing names and points of the 3 first players

  leaderboard(best_players, &best_players_number); //getting the leaderboard

  buttons->b = malloc((best_players_number+2) * sizeof(Sprite_t)); //allocating memory for 5 buttons
  buttons->length = best_players_number+2; //setting length

  createButton(&(buttons->b[0]), 0, screen->h * 0.02, TTF_RenderText_Blended(title_font, "Leaderboard :", color), NULL); //creating The title (button that do not trigger anything)
  SDL_BlitSurface(buttons->b[0].bmp, NULL, screen, &(buttons->b[0].rect)); //updating the title to initialize rect.w and rect.h
  buttons->b[0].rect.x = screen -> w/2 - buttons->b[0].rect.w / 2; //setting the title in the middle

  for(i = 1; i < best_players_number+1; i++) //for each player, creating text
  {
    createButton(&(buttons->b[i]), 0, (i+1) * screen->h * 0.12, TTF_RenderText_Blended(text_font, best_players[i-1], color), NULL);
    SDL_BlitSurface(buttons->b[i].bmp, NULL, screen, &(buttons->b[i].rect));
    buttons->b[i].rect.x = screen -> w/2 - buttons->b[i].rect.w / 2;
  }

  createButton(&(buttons->b[best_players_number+1]), screen->w / 2 - 225 / 2, screen->h * 0.6, SDL_LoadBMP("assets/sprite/button/menu_button4.bmp"), returnToMenu); //button to return to main menu

  TTF_CloseFont(title_font); //closing the font
  TTF_CloseFont(text_font);
}
