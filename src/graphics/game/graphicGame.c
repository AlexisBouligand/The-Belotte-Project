#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "graphics/SDLCheck.h"
#include "game/variableManagement.h"
#include "graphics/game/graphicGame.h"
#include "graphics/button.h"
#include "game/game.h"


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
  Sprite_t spr_title;
  spr_title.rect.x = 220;
  spr_title.rect.y = 10;
  Sprite_t spr_score1;
  spr_score1.rect.x = 220;
  spr_score1.rect.y = 250;
  Sprite_t spr_score2;
  spr_score2.rect.x = 220;
  spr_score2.rect.y = 350;
  Sprite_t spr_space;
  spr_space.rect.x = 220;
  spr_space.rect.y = 450;

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
  spr_title.bmp = TTF_RenderText_Solid(font, title, lightBrown);
  spr_score1.bmp = TTF_RenderText_Solid(font, txt1, lightBrown);
  spr_score2.bmp = TTF_RenderText_Solid(font, txt2, lightBrown);
  spr_space.bmp = TTF_RenderText_Solid(font, space, lightBrown);

  //We Blit
  SDL_BlitSurface(background,NULL,screen,NULL);
  SDL_BlitSurface(txt_title.bmp,NULL,screen, &txt_title.rect);
  SDL_BlitSurface(txt_score1.bmp,NULL,screen, &txt_score1.rect);
  SDL_BlitSurface(txt_score2.bmp,NULL,screen, &txt_score2.rect);
  SDL_BlitSurface(txt_space.bmp,NULL,screen, &txt_space.rect);
  SDL_BlitSurface(spr_title.bmp,NULL,screen, &spr_title.rect);
  SDL_BlitSurface(spr_score1.bmp,NULL,screen, &spr_score1.rect);
  SDL_BlitSurface(spr_score2.bmp,NULL,screen, &spr_score2.rect);
  SDL_BlitSurface(spr_space.bmp,NULL,screen, &spr_space.rect);

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
  SDL_FreeSurface(spr_title.bmp);
  SDL_FreeSurface(spr_score1.bmp);
  SDL_FreeSurface(spr_score2.bmp);
  SDL_FreeSurface(spr_space.bmp);
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
  Sprite_t spr_title;
  spr_title.rect.x = 220;
  spr_title.rect.y = 10;
  Sprite_t spr_result;
  spr_result.rect.x = 220;
  spr_result.rect.y = 250;
  Sprite_t spr_space;
  spr_space.rect.x = 220;
  spr_space.rect.y = 450;

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
  spr_title.bmp = TTF_RenderText_Solid(font, title, lightBrown);
  checkError(spr_title.bmp);

  txt_result.bmp = TTF_RenderText_Solid(font, result, lightBrown);
  checkError(txt_result.bmp);
  spr_result.bmp = TTF_RenderText_Solid(font, result, lightBrown);
  checkError(spr_result.bmp);

  txt_space.bmp = TTF_RenderText_Solid(font, space, lightBrown);
  checkError(txt_space.bmp);
  spr_space.bmp = TTF_RenderText_Solid(font, space, lightBrown);
  checkError(spr_space.bmp);


  //We Blit
  SDL_BlitSurface(background,NULL,screen,NULL);
  SDL_BlitSurface(txt_title.bmp,NULL,screen, &txt_title.rect);
  SDL_BlitSurface(txt_result.bmp,NULL,screen, &txt_result.rect);
  SDL_BlitSurface(txt_space.bmp,NULL,screen, &txt_space.rect);
  SDL_BlitSurface(spr_title.bmp,NULL,screen, &spr_title.rect);
  SDL_BlitSurface(spr_result.bmp,NULL,screen, &spr_result.rect);
  SDL_BlitSurface(spr_space.bmp,NULL,screen, &spr_space.rect);

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
  SDL_FreeSurface(spr_title.bmp);
  SDL_FreeSurface(spr_result.bmp);
  SDL_FreeSurface(spr_space.bmp);
  TTF_CloseFont(font);
}

void displayPassesResult(SDL_Surface *screen, SDL_Surface *background, Player_t players[], char trump)
{
  TTF_Font *font = NULL;
  font = TTF_OpenFont("assets/font/Minecraft.ttf", 60);
  checkFont(font);
  SDL_Color lightBrown = {99,92,92};

  //The sprites displayed
  Sprite_t spr_bet;
  spr_bet.rect.x = 220;
  spr_bet.rect.y = 200;
  Sprite_t spr_trump;
  spr_trump.rect.x = 220;
  spr_trump.rect.y = 275;
  Sprite_t spr_space;
  spr_space.rect.x = 220;
  spr_space.rect.y = 450;

  //the texts displayed on the sprites
  char txt_bet[35];
  char txt_trump[45];
  char txt_space[25]="Press space to continue";

  //logic to know what to display
  int bet = 0;
  int team_bet_id;
  int i;
  for (i = 0; i < 4; i++)
  {
    if(players[i].bet > bet)
    {
      bet = players[i].bet;
      team_bet_id = i % 2;
    }
  }

  if (team_bet_id==0)//user's team placed the bet
  {
    sprintf(txt_bet, "Your team placed a %d bet", bet);
  }
  else
  {
    sprintf(txt_bet, "The other team placed a %d bet", bet);
  }

  switch(trump)
  {
    case 'D'  :
      sprintf(txt_trump, "This round is played with Diamond trump");
      break;
    case 'C'  :
      sprintf(txt_trump, "This round is played with Club trump");
      break;
    case 'H'  :
      sprintf(txt_trump, "This round is played with Heart trump");
      break;
    case 'S'  :
      sprintf(txt_trump, "This round is played with Spade trump");
      break;
    case 'N'  :
      sprintf(txt_trump, "This round is played with No trump");

      break;
    case 'A'  :
      sprintf(txt_trump, "This round is played with All trump");
      break;
    default :
      sprintf(txt_trump, "Error : Trump not found");
      sprintf(txt_trump, "error:Trump not available");

 }

  //Render the txts on the sprites
  spr_bet.bmp = TTF_RenderText_Solid(font, txt_bet, lightBrown);
  checkError(spr_bet.bmp);

  spr_trump.bmp = TTF_RenderText_Solid(font, txt_trump, lightBrown);
  checkError(spr_trump.bmp);

  spr_space.bmp = TTF_RenderText_Solid(font, txt_space, lightBrown);
  checkError(spr_space.bmp);

  //We Blit
  SDL_BlitSurface(background,NULL,screen,NULL);
  SDL_BlitSurface(spr_bet.bmp,NULL,screen, &spr_bet.rect);
  SDL_BlitSurface(spr_trump.bmp,NULL,screen, &spr_trump.rect);
  SDL_BlitSurface(spr_space.bmp,NULL,screen, &spr_space.rect);

  SDL_Flip(screen);

  SDL_Event event;
  int exit_loop = 0;
  while (exit_loop!=1)
  {
    SDL_WaitEvent(&event);
    if (event.key.keysym.sym==SDLK_SPACE)
    {
          exit_loop++;
    }
  }

  //we free
  SDL_FreeSurface(spr_bet.bmp);
  SDL_FreeSurface(spr_trump.bmp);
  SDL_FreeSurface(spr_space.bmp);
  TTF_CloseFont(font);
}
