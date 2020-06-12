#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "graphics/SDLCheck.h"
#include "game/variableManagement.h"
#include "graphics/game/graphicGame.h"
#include "graphics/button.h"


Card_t graphicPlayerCardChoice(Card_t  player_hand[8], Card_t table_cards[4], SDL_Surface *screen, SDL_Surface *background)
{



    //We blit one time for the initialization of card_sprites(to get the good dimensions set in displayPlayerCards)
    SDL_BlitSurface(background, NULL, screen, NULL);
    graphicDisplayPlayerCards(player_hand, screen);

    int number_of_card_played = -1;//The variable we will return
    //Needed for the card to be considered as a button
    Sprite_t card_sprite[8];
     for(int i = 0 ; i<8 ; i++)
    {
        card_sprite[i] = player_hand[i].card_sprite;
    }


    int looping = 1;


    while(looping)
    {

        number_of_card_played = buttonPressed(card_sprite, 8);
        //We will return the card played if there is one
        if( number_of_card_played != -1)
        {
            looping = 0;
        }



        //We make all the Blit
        SDL_BlitSurface(background, NULL, screen, NULL);
        graphicDisplayPlayerCards(player_hand, screen);
        graphicDisplayTableCards(table_cards, screen);




        SDL_Flip(screen);


    }


     return player_hand[number_of_card_played];


}



void graphicDisplayPlayerCards(Card_t player_hand[8], SDL_Surface *screen)
{

        for(int i = 0 ; i<8 ; i++)
        {
            if(player_hand[i].color != 0)
            {
            //The position
            player_hand[i].card_sprite.rect.y = 600;
            player_hand[i].card_sprite.rect.x = i*200 + 20;

            //We set the transparency
            SDL_SetColorKey(player_hand[i].card_sprite.bmp, SDL_SRCCOLORKEY, SDL_MapRGB(player_hand[i].card_sprite.bmp->format,0,255,0));
            //We blit the surface
            SDL_BlitSurface(player_hand[i].card_sprite.bmp, NULL, screen, &player_hand[i].card_sprite.rect );
            }
        }
}



void graphicDisplayTableCards(Card_t table_cards[4], SDL_Surface *screen)
{



    for(int i = 0 ; i<4 ; i++)
    {
        if(table_cards[i].color != 0 )
        {
            //The position
            table_cards[i].card_sprite.rect.y = 300;
            table_cards[i].card_sprite.rect.x = i*300 + 260;
            //We set the transparency
            SDL_SetColorKey(table_cards[i].card_sprite.bmp, SDL_SRCCOLORKEY, SDL_MapRGB(table_cards[i].card_sprite.bmp->format,0,255,0));
            //We blit the surface
            SDL_BlitSurface(table_cards[i].card_sprite.bmp, NULL, screen, &table_cards[i].card_sprite.rect );
        }

    }
}




void displayAfterPlayerChoice(Card_t player_hand[8], Card_t table_cards[4], SDL_Surface *screen, SDL_Surface *background)
{

    SDL_Event event;

    int looping = 1;

    TTF_Font *font = NULL;
    font = TTF_OpenFont("assets/font/Minecraft.ttf", 60);
    checkFont(font);
    SDL_Color lightBrown = {99,92,92};

    Sprite_t txt_space = {.bmp = TTF_RenderText_Solid(font, "Press space to continue", lightBrown)};
    checkError(txt_space.bmp);

    //The loop will stop when the space bar is pressed
    while(looping)
    {

        SDL_WaitEvent(&event);

        if(event.key.keysym.sym == SDLK_SPACE)
        {
          looping = 0;
        }



        //We make all the Blit
        SDL_BlitSurface(background, NULL, screen, &(txt_space.rect));
        SDL_BlitSurface(txt_space.bmp, NULL, screen, NULL);

        graphicDisplayPlayerCards(player_hand, screen);
        graphicDisplayTableCards(table_cards, screen);


        SDL_Flip(screen);


    }

    SDL_FreeSurface(txt_space.bmp);

}

void displayScores(SDL_Surface *screen, SDL_Surface *background, int score1, int score2)
{
  TTF_Font *font = NULL;
  font = TTF_OpenFont("assets/font/Minecraft.ttf", 60);
  checkFont(font);
  SDL_Color lightBrown = {99,92,92};

  //The text displayed
  Sprite_t txt_title;
  txt_title.rect.x = 220;
  txt_title.rect.y = 10;
  Sprite_t txt_score1;
  txt_score1.rect.x = 220;
  txt_score1.rect.y = 250;
  Sprite_t txt_score2;
  txt_score2.rect.x = 220;
  txt_score2.rect.y = 350;
  Sprite_t txt_space;
  txt_space.rect.x = 220;
  txt_space.rect.y = 450;

  char title[25]="Teams points";
  char txt1[19];
  char txt2[19];
  char space[25]="Press space to continue";
  //We set the surface for the text diplayed
  sprintf(txt1, "Your Team : %d", score1);
  sprintf(txt2, "AI's Team : %d", score2);
  txt_title.bmp = TTF_RenderText_Solid(font, title, lightBrown);
  txt_score1.bmp = TTF_RenderText_Solid(font, txt1, lightBrown);
  txt_score2.bmp = TTF_RenderText_Solid(font, txt2, lightBrown);
  txt_space.bmp = TTF_RenderText_Solid(font, space, lightBrown);

  //We Blit
  SDL_BlitSurface(background,NULL,screen,NULL);
  SDL_BlitSurface(txt_title.bmp,NULL,screen, &txt_title.rect);
  SDL_BlitSurface(txt_score1.bmp,NULL,screen, &txt_score1.rect);
  SDL_BlitSurface(txt_score2.bmp,NULL,screen, &txt_score2.rect);
  SDL_BlitSurface(txt_space.bmp,NULL,screen, &txt_space.rect);

  SDL_Flip(screen);

  SDL_Event event;
  int exit_loop = 0;
  while (exit_loop!=2)
  {
    SDL_WaitEvent(&event);
    if (event.key.keysym.sym==SDLK_SPACE)
    {
          exit_loop++;
    }
  }

  SDL_FreeSurface(txt_title.bmp);
  SDL_FreeSurface(txt_score1.bmp);
  SDL_FreeSurface(txt_score2.bmp);
  SDL_FreeSurface(txt_space.bmp);
  TTF_CloseFont(font);

}

void displayGameOver(SDL_Surface *screen, SDL_Surface *background, int win)
{
  TTF_Font *font = NULL;
  font = TTF_OpenFont("assets/font/Minecraft.ttf", 60);
  checkFont(font);
  SDL_Color lightBrown = {99,92,92};

  //The text displayed
  Sprite_t txt_title;
  txt_title.rect.x = 220;
  txt_title.rect.y = 10;
  Sprite_t txt_result;
  txt_result.rect.x = 220;
  txt_result.rect.y = 250;
  Sprite_t txt_space;
  txt_space.rect.x = 220;
  txt_space.rect.y = 450;

  char title[25]="Game Over";
  char result[19];
  char space[25]="Press space to continue";
  //We set the surface for the text diplayed
  if (win)
  {
    sprintf(result, "You won :D");
  }
  else
  {
    sprintf(result, "You lose :'<");
  }
  txt_title.bmp = TTF_RenderText_Solid(font, title, lightBrown);
  checkError(txt_title.bmp);

  txt_result.bmp = TTF_RenderText_Solid(font, result, lightBrown);
  checkError(txt_result.bmp);

  txt_space.bmp = TTF_RenderText_Solid(font, space, lightBrown);
  checkError(txt_space.bmp);


  //We Blit
  SDL_BlitSurface(background,NULL,screen,NULL);
  SDL_BlitSurface(txt_title.bmp,NULL,screen, &txt_title.rect);
  SDL_BlitSurface(txt_result.bmp,NULL,screen, &txt_result.rect);
  SDL_BlitSurface(txt_space.bmp,NULL,screen, &txt_space.rect);

  SDL_Flip(screen);

  SDL_Event event;
  int exit_loop = 0;
  while (exit_loop!=2)
  {
    SDL_WaitEvent(&event);
    if (event.key.keysym.sym==SDLK_SPACE)
    {
          exit_loop++;
    }
  }

  SDL_FreeSurface(txt_title.bmp);
  SDL_FreeSurface(txt_result.bmp);
  SDL_FreeSurface(txt_space.bmp);
  TTF_CloseFont(font);
}
