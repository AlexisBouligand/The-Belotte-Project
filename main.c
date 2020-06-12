#include <stdio.h>
#include <ctype.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "graphics/button.h"
#include "graphics/menu/mainmenu.h"
#include "graphics/menu/start.h"
#include "graphics/menu/credits.h"
#include "graphics/menu/leaderboard.h"
#include "game/game.h"
#include "graphics/SDLCheck.h"

//compiling options for atom
//-L lib -I include src/game/*.c src/menu/*.c src/graphics/*.c src/graphics/menu/*.c src/graphics/game/*.c -lmingw32 -lSDLmain -lSDL -lSDL_ttf

int getButtonsEvent(SDL_Surface *screen, Array_of_buttons_t *buttons, SDL_Event event, char *cargs) //function that checks if user has clicked on a button and execute it's function
{
  int i;
  if(event.type == SDL_MOUSEBUTTONDOWN ) //mouse clicked
  {
    if(event.button.button == SDL_BUTTON_LEFT) //left mouse button
    {
      for(i = 0; i < buttons->length; i++) //for each button
      {
        //checking mouse coordinates are inside the button, if the button is enabled and it's function is not NULL (used for text)
        if(checkMouseCoordinates(buttons->b[i], event.button.x, event.button.y) && buttons->b[i].enabled && buttons->b[i].onClick != NULL)
        {
          return buttons->b[i].onClick(&(buttons->b[i]), &i, NULL); //returning button's value corresponding to a section 0 to 3 (start, leaderboard, etc.)
        }
      }
    }

  } else if(event.type == SDL_QUIT)
  {
    return 4; //4 means to exit the menu
  }

  return -1; //-1 means that we stay in the actual section
}

//getStartEvents(SDL_Surface *screen, Array_of_buttons_t *buttons, SDL_Event event);


int main(int argc, char *argv[])
{
  int section = 0; //0 : main menu, 1 : start, 2 : leaderboard, 3 : Credits, 4 : exit menu
  int i; //counter
  int exit_menu = 0; //variable to check if we exit the menu
  int exit_loop = -1; //variable to check if we exit the event loop (-1 means no)
  char player_name[20] = "_"; //variable that will contain player's name

  freopen("CON", "w", stdout); //stdout int the console and not stdout.txt
  freopen("CON", "w", stderr); //same than stdout

  //array containing function pointers for each section initialization.
  void (*init_functions[])(SDL_Surface *, Array_of_buttons_t *) = {initMenu, initStart, initLeader, initCredits};

  //array containing the event loop to execute for each section
  int (*loop_functions[])(SDL_Surface *, Array_of_buttons_t *, SDL_Event, char *) = {getButtonsEvent, getButtonAndKeysEvent, getButtonsEvent, getButtonsEvent};

  SDL_Init(SDL_INIT_VIDEO); //initialiazing SDL
  TTF_Init(); //initializing SDL_TTF

  SDL_Surface *screen = SDL_SetVideoMode(1600, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Creating the screen
  checkError(screen);
  SDL_Surface *background = SDL_LoadBMP("assets/sprite/Background.bmp"); //creating the background
  checkError(background);
  SDL_Rect background_position = {.x = 0, .y = 0}; //background's position

  while(!exit_menu)
  {
    Array_of_buttons_t buttons; //dynamic array containg buttons of each section

    init_functions[section](screen, &buttons); //initializing the section
    do { //event loop
      SDL_Event event;
      SDL_WaitEvent(&event); //getting event

      exit_loop = loop_functions[section](screen, &buttons, event, player_name); //checking events

      if(exit_loop == 4)
      {
        exit_menu = 1;
      }

      SDL_BlitSurface(background, NULL, screen, &background_position); //printing the background in the screen

      for(i = 0; i < buttons.length; i++)
      {
        SDL_BlitSurface(buttons.b[i].bmp, NULL, screen, &(buttons.b[i].rect)); //printing each buttons on the screen
      }
      SDL_Flip(screen); //updating the screen

    } while(exit_loop < 0);

    section = exit_loop;

    freeButtonSurface(buttons.b, buttons.length); //removing each button from SDL memory

    free(buttons.b); //removing buttons from memory

    if(section == 5) //section 5 means to start the game loop
    {
      gameLoop(screen, background, player_name);
      section = 0;
    }
  }

  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);

  TTF_Quit();
  SDL_Quit();
  system("pause");
}
