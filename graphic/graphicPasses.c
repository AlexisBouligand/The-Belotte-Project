#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "basicFunc.h"
#include "graphicPasses.h"
#include "button.h"
#include "../game.h"
#include "graphicGame.h"

SDL_Surface *pass_screen =NULL;

void initializePassWindow()
{
  //Window initisalization
    SDL_Init(SDL_INIT_VIDEO);
    pass_screen = SDL_SetVideoMode(1600,900,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);//We set the window with video only, double buffering and full pass_screen
    checkError(pass_screen);
}

int graphicGetBet(int *max, Card_t *player_hand, Player_t *player_and_AI)
{


    //Font initialization
    TTF_Init();
    TTF_Font *font = NULL;
    font = TTF_OpenFont("font/rainyhearts.ttf", 60);
    checkFont(font);
    SDL_Color lightBrown = {198,183,184};

    //We create the background
    SDL_Surface *background = NULL;
    background = SDL_LoadBMP("graphic/sprite/Background.bmp");//! We need to free the surface at the end
    checkError(background);

    //The text displayed = the bet
    Sprite_t playerBet;
    playerBet.rect.x = 775;
    playerBet.rect.y = 420;

    char numberBet[10];



    int value = 82;//The value we return

    //The buttons displayed
    Sprite_t buttons[4];
    betButtonInitialization(buttons);

    //We set the default value
    if(*max == 0)
    {
        value = 82;
    }
    else{
        value = *max;
    }
    int looping = 1;




    while(looping)
    {
        //We check if the player click on the mouse
        //The action depend on the button pressed
        switch(buttonPressed(buttons, 4))
        {
            case 0:
                if(value>82 && value>*max)
                {
                    value-=10;

                }
            break;

            case 1:
                if(value<152)
                {
                    value += 10;
                }
            break;

            case 2:
                value = 0;
                looping = 0;
            break;

            case 3:
                looping = 0;
            break;
        }

        //We set the surface for the text diplayed
        sprintf(numberBet, "%d", value);
        playerBet.bmp = TTF_RenderText_Solid(font, numberBet, lightBrown);

        //We change the color to white to reload the pass_screen
        SDL_FillRect(pass_screen, NULL, SDL_MapRGB(pass_screen->format, 255,255,255));



        //We make all the Blit
        SDL_BlitSurface(background, NULL, pass_screen, NULL);
        for(int i= 0 ;i<4 ; i++)
        {
            SDL_BlitSurface(buttons[i].bmp, NULL, pass_screen, &buttons[i].rect);
        }
        SDL_BlitSurface(playerBet.bmp,NULL,pass_screen, &playerBet.rect);//We diaplay the text
        graphicDisplayPlayerCards(player_hand, pass_screen);
        displayAIBet(player_and_AI, font, lightBrown);

        SDL_Flip(pass_screen);


    }

    TTF_Quit();
    SDL_FreeSurface(background);

    *max = value;
    return value;
}




char graphicGetTrump()
{
    SDL_Event event;



    //We create the background
    SDL_Surface *background = NULL;
    background = SDL_LoadBMP("graphic/sprite/Background.bmp");//! We need to free the surface at the end
    checkError(background);





    char trump = 'X';//The trump we return

    Sprite_t buttons[6];
    trumpButtonInitialization(buttons);

    int looping = 1;




    while(looping)
    {
        //We check if the player click on the mouse
        switch(buttonPressed(buttons, 6))
        {
            case 0:
                trump = 'S';
                looping = 0;
            break;

            case 1:
                trump = 'C';
                looping = 0;
            break;

            case 2:
                trump = 'D';
                looping = 0;
            break;

            case 3:
                trump = 'H';
                looping = 0;
            break;
             case 4:
                trump = 'N';
                looping = 0;
            break;
             case 5:
                trump = 'A';
                looping = 0;
            break;
        }


        //We change the color to white to reload the pass_screen
        SDL_FillRect(pass_screen, NULL, SDL_MapRGB(pass_screen->format, 255,255,255));



        //We make all the Blit
        SDL_BlitSurface(background, NULL, pass_screen, NULL);
        for(int i= 0 ;i<6 ; i++)
        {
            SDL_BlitSurface(buttons[i].bmp, NULL, pass_screen, &buttons[i].rect);
        }



        SDL_Flip(pass_screen);


    }
    SDL_FreeSurface(background);
    //We return the trump choosen
    return trump;
}


void displayAIBet(Player_t *player_an_AI, TTF_Font *font, SDL_Color color)
{
    Sprite_t text;
    text.rect.y = 200;
    text.rect.x = 350;
    //String needed to set text
    char AIBet[20] = "AI :";
    char AIName[2],  AIBetValue[4];
    for(int i = 0; i<4 ; i++)
    {
        //If it is not the player bet and If the AI has made a bet
        if(player_an_AI[i].id != 0 && player_an_AI[i].bet != 0)
        {

            //We set the AIBet = text, which will be displayed
            sprintf(AIName, "%d", player_an_AI[i].id);
            AIBet[2] = AIName[0];

            AIBet[4] = player_an_AI[i].trump;
            AIBetValue[2] = ' ';
            sprintf(AIBetValue, "%d", player_an_AI[i].bet);
            AIBet[5] = AIBetValue[0];
            AIBet[6] = AIBetValue[1];
            AIBet[7] = AIBetValue[2];



            //We blit the surface
            text.rect.x +=200;
            text.bmp = TTF_RenderText_Solid(font, AIBet, color);
            SDL_BlitSurface(text.bmp, NULL, pass_screen, &text.rect);

        }
    }

}


void betButtonInitialization(Sprite_t bet_button[4])
{


    //File
    bet_button[0].bmp = SDL_LoadBMP("graphic/sprite/button/left_arrow.bmp");
    bet_button[1].bmp = SDL_LoadBMP("graphic/sprite/button/right_arrow.bmp");
    bet_button[2].bmp = SDL_LoadBMP("graphic/sprite/button/pass_button.bmp");
    bet_button[3].bmp = SDL_LoadBMP("graphic/sprite/button/continue_button.bmp");

    //Check for error
    for(int i =0; i<4 ; i++)
    {
        checkError(bet_button[i].bmp);
    }


    //Position
    SDL_Rect fixed_position;
    fixed_position.x = 775;
    fixed_position.y = 420;

    bet_button[0].rect.x = fixed_position.x -100;
    bet_button[0].rect.y = fixed_position.y ;
    bet_button[1].rect.x = fixed_position.x + 100 ;
    bet_button[1].rect.y = fixed_position.y ;
    bet_button[2].rect.x = fixed_position.x - 165 ;
    bet_button[2].rect.y = fixed_position.y + 100;
    bet_button[3].rect.x = fixed_position.x + 100;
    bet_button[3].rect.y = fixed_position.y + 100;
}


void trumpButtonInitialization(Sprite_t trump_button[6])
{
    //file
    trump_button[0].bmp = SDL_LoadBMP("graphic/sprite/button/trump_button1.bmp");
    trump_button[1].bmp = SDL_LoadBMP("graphic/sprite/button/trump_button2.bmp");
    trump_button[2].bmp = SDL_LoadBMP("graphic/sprite/button/trump_button3.bmp");
    trump_button[3].bmp = SDL_LoadBMP("graphic/sprite/button/trump_button4.bmp");
    trump_button[4].bmp = SDL_LoadBMP("graphic/sprite/button/trump_button5.bmp");
    trump_button[5].bmp = SDL_LoadBMP("graphic/sprite/button/trump_button6.bmp");

    //check for erro
      for(int i =0; i<6 ; i++)
    {
        checkError(trump_button[i].bmp);
    }

    //Position
    SDL_Rect fixed_position;
    fixed_position.x = 750;
    fixed_position.y = 420;

    trump_button[0].rect.x = fixed_position.x-200;
    trump_button[0].rect.y = fixed_position.y;
    trump_button[1].rect.x = fixed_position.x-100;
    trump_button[1].rect.y = fixed_position.y;
    trump_button[2].rect.x = fixed_position.x;
    trump_button[2].rect.y = fixed_position.y;
    trump_button[3].rect.x = fixed_position.x+100;
    trump_button[3].rect.y = fixed_position.y;
    trump_button[4].rect.x = fixed_position.x+200;
    trump_button[4].rect.y = fixed_position.y;
    trump_button[5].rect.x = fixed_position.x+300;
    trump_button[5].rect.y = fixed_position.y;
}
