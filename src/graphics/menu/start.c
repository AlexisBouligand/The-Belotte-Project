#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include "graphics/menu/start.h"
#include "graphics/menu/mainmenu.h"
#include "graphics/SDLCheck.h"

int startGame(Sprite_t *button, int *iargs, char *cargs)
{
  if (cargs[*iargs] == '_')
  {
    cargs[*iargs] = '\0'; //remvoing _ from the end of the name
  }
  printf("C'est partit %s\n", cargs);
  return 5; //exiting the menu
}

void initStart(SDL_Surface *screen, Array_of_buttons_t *buttons)
{
  TTF_Font *font = TTF_OpenFont("assets/font/Minecraft.ttf", 65); //using times.ttf font with a size of 65
  checkFont(font);

  TTF_SetFontStyle(font, TTF_STYLE_BOLD); //set to bold
  SDL_Color color = {99, 92, 92}; //color of the font
  int i; //counter
  char *text[] = {"Enter your name :", "_"}; //array containing each text sprites.

  buttons->b = malloc(4 * sizeof(Sprite_t)); //allocating memory for 4 buttons
  buttons->length = 4; //setting length

  for(i = 0; i < 2; i++)
  {
    createButton(&(buttons->b[i]), 0, (i * 14 + 1) * screen->h * 0.02, TTF_RenderText_Blended(font, text[i], color), NULL); //creating text sprite (button that do not trigger anything)
    SDL_BlitSurface(buttons->b[i].bmp, NULL, screen, &(buttons->b[i].rect)); //updating the text to initialize rect.w and rect.h
    buttons->b[i].rect.x = screen -> w/2 - buttons->b[i].rect.w / 2; //setting the text in the middle
  }

  createButton(&(buttons->b[2]), screen->w / 2 - 225 / 2, screen->h * 0.48, SDL_LoadBMP("assets/sprite/button/menu_button1.bmp"), startGame); //button to start the game
  createButton(&(buttons->b[3]), screen->w / 2 - 225 / 2, screen->h * 0.6, SDL_LoadBMP("assets/sprite/button/menu_button4.bmp"), returnToMenu); //button to return to menu

  TTF_CloseFont(font); //closing the font
}

int getButtonAndKeysEvent(SDL_Surface *screen, Array_of_buttons_t *buttons, SDL_Event event, char *name)
{
  static int upper = 0; //variable that checks if we want an uppercase letter (RSHIFT / LEFTSHIFT)
  static int cursor = 0; //current position int the name array
  static int toggle_font = 1; //variable that checks if we have to reinitialazing the font (when we exit the section the font is closed)
  int i; //counter

  static TTF_Font *font;
  SDL_Color color = {99, 92, 92};

  if(toggle_font)
  {
    font = TTF_OpenFont("assets/font/Minecraft.ttf", 65);
    checkFont(font);

    toggle_font = 0;
  }

  switch(event.type)
  {
    case SDL_QUIT: //if we click on the cross
      return 4; //exiting menu
      break;
    case SDL_KEYDOWN: //if a key is pressed
      switch(event.key.keysym.sym) //getting key id
      {
        case SDLK_LSHIFT: //left shift or right shift
        case SDLK_RSHIFT:
          upper = 1; //upper case enabled
          break;

        case SDLK_BACKSPACE: //backspace
          if(cursor > 0) //if there is at least one letter
          {
            name[cursor-1] = '_'; //removing the letter
            name[cursor] = '\0';
            cursor--; //moving the cursor
          }
          break;

        case 32 ... 126: //each possible character
          if(cursor < 20) //max name length
          {
            if(upper)
            {
              name[cursor] = toupper(event.key.keysym.sym); //making the letter uppercase
            }
            else
            {
              name[cursor] = event.key.keysym.sym;
            }

            if(cursor<19) //removing the '_' if there is no more place
            {
              name[cursor+1] = '_';
              name[cursor+2] = '\0';
            } else {
              name[cursor+1] = '\0';
            }
            cursor++; //increasing the cursor
          }
          break;
        }
        break;


    case SDL_KEYUP: //if a key is released
      if(event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
      {
        upper = 0; //toggle the uppercase
      }
      break;


    case SDL_MOUSEBUTTONDOWN: //same as getButtonsEvent
      if(event.button.button == SDL_BUTTON_LEFT)
      {
        for(i = 0; i < buttons->length; i++)
        {
          if(checkMouseCoordinates(buttons->b[i], event.button.x, event.button.y) && buttons->b[i].enabled && buttons->b[i].onClick != NULL)
          {
            TTF_CloseFont(font);
            toggle_font = 1;
            return buttons->b[i].onClick(&(buttons->b[i]), &cursor, name); //setting as arguments cursor's position (for name length) and the name
          }
        }
      }
      break;
  }

  buttons->b[2].enabled = (cursor > 0); //enable start button if at least a letter is entered

  buttons->b[1].bmp = TTF_RenderText_Blended(font, name, color); //updating the text with the name
  buttons->b[1].rect.x = screen->w / 2 - buttons->b[1].rect.w / 2; //recentering the text
  return -1; //continue the loop
}
