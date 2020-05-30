#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "basicFunc.h"
#include "../variableManagement.h"
#include "graphicGame.h"
#include "button.h"
#include "../gameInput.h"


//Global variable
SDL_Surface *screen = NULL;

Card_t graphicPlayerCardChoice(Card_t  player_hand[8], Card_t table_cards[4])
{

    SDL_Event event;

    //Window initisalization
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1600,900,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);//We set the window with video only, double buffering and full screen
    checkError(screen);

    //We create the background
    SDL_Surface *background = NULL;
    background = SDL_LoadBMP("graphic/sprite/Background.bmp");//! We need to free the surface at the end
    checkError(background);



    //We blit one time for the initialization of card_sprites(to get the good dimensions set in displayPlayerCards)
    SDL_BlitSurface(background, NULL, screen, NULL);
    graphicDisplayPlayerCards(player_hand);

    int number_of_card_played = -1;
    Sprite_t card_sprite[8];//Needed for the card to be considered as a button
     for(int i = 0 ; i<8 ; i++)
    {
        card_sprite[i] = player_hand[i].card_sprite;
    }

    //Variables for the timer ; the cards are displayed a last time before the next trick
    int timer_duration = 1000;
    int current_time = 0;
    int previous_time = 0;

    int looping = 1;


    while(looping)
    {
        //We return the card played if it exist
        number_of_card_played = buttonPressed(card_sprite, 8);
        if(player_hand[number_of_card_played].color !=0 && number_of_card_played != -1)
        {
            looping = 0;
        }


        //We change the color to white to reload the screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,255,255));



        //We make all the Blit
        SDL_BlitSurface(background, NULL, screen, NULL);
        graphicDisplayPlayerCards(player_hand);
        graphicDisplayTableCards(table_cards);




        SDL_Flip(screen);


    }

     return player_hand[number_of_card_played];

}



void graphicDisplayPlayerCards(Card_t player_hand[8])
{

        for(int i = 0 ; i<8 ; i++)
        {
            if(player_hand[i].color != 0)
            {
            //The position
            player_hand[i].card_sprite.rect.y = 500;
            player_hand[i].card_sprite.rect.x = i*200 + 20;

            //We set the transparency
            SDL_SetColorKey(player_hand[i].card_sprite.bmp, SDL_SRCCOLORKEY, SDL_MapRGB(player_hand[i].card_sprite.bmp->format,0,255,0));
            //We blit the surface
            SDL_BlitSurface(player_hand[i].card_sprite.bmp, NULL, screen, &player_hand[i].card_sprite.rect );
            }
        }
}



void graphicDisplayTableCards(Card_t table_cards[4])
{


    int i =0;
    for(int i = 0 ; i<4 ; i++)
    {


        if(table_cards[i].color != 0 )
        {

            table_cards[i].card_sprite.rect.y = 200;
            table_cards[i].card_sprite.rect.x = i*300 + 100;

            SDL_SetColorKey(table_cards[i].card_sprite.bmp, SDL_SRCCOLORKEY, SDL_MapRGB(table_cards[i].card_sprite.bmp->format,0,255,0));

            SDL_BlitSurface(table_cards[i].card_sprite.bmp, NULL, screen, &table_cards[i].card_sprite.rect );
        }


    }
}




void displayAfterPLayerChoicee(Card_t player_hand[8], Card_t table_cards[4])
{

    SDL_Event event;

    int looping = 1;

     //We create the background
    SDL_Surface *background = NULL;
    background = SDL_LoadBMP("graphic/sprite/Background.bmp");//! We need to free the surface at the end
    checkError(background);

    //The lo0p will stop when the space bar is pressed
    while(looping)
    {



        SDL_WaitEvent(&event);
        switch(event.key.keysym.sym)
        {
        case SDLK_SPACE:
            looping = 0;
        }


        //We change the color to white to reload the screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,255,255));



        //We make all the Blit
        SDL_BlitSurface(background, NULL, screen, NULL);
        graphicDisplayPlayerCards(player_hand);
        graphicDisplayTableCards(table_cards);




        SDL_Flip(screen);


    }

}
