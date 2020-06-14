#ifndef GRAPHICGAME_H_INCLUDED
#define GRAPHICGAME_H_INCLUDED
#include <SDL/SDL.h>
#include "game/variableManagement.h"
#include "game/game.h"

///All the following function ask for the screen surface and/or the background///

//Need all the player and AI cards
//The base of the graphical game window where the player choose his cards
//Return the chosen card of the player
Card_t graphicPlayerCardChoice(Card_t player_hand[8], Card_t table_cards[4], SDL_Surface *screen, SDL_Surface *background);

//Ask for hte player hand and the surface on which the hand will be display(needed in another window)
//Display the hand and set a position value to the cards
void graphicDisplayPlayerCards(Card_t player_hand[8], SDL_Surface *screen);

//Ask for the Table cards
//Display them
void graphicDisplayTableCards(Card_t table_cards[4], SDL_Surface *screen);

//Ask for the player hand and the table card
//Display them after the player turn. Else, the player cannot see what the AI play after his/her turn
void displayAfterPlayerChoice(Card_t player_hand[8], Card_t table_cards[4], SDL_Surface *screen, SDL_Surface *background);

//Need the team scores
//Displays the teams scores
//To be called at the end of each round
//Quits when the user hits the space key
//Have to be called at the end of each round
void displayScores(SDL_Surface *screen, SDL_Surface *background, int score1, int score2);

//Need a boolean to know who won the game
//Displays the game over screen
//Quits to the main menu when the user hits the space key
void displayGameOver(SDL_Surface *screen, SDL_Surface *background, int win);

//Need the player's informations to know what are the results of the passes
//Displays the bet placed, trump color (or all or no trump)
//Quits to the main menu when the user hits the space key
void displayPassesResult(SDL_Surface *screen, SDL_Surface *background, Player_t players[], char trump);

#endif // GRAPHICGAME_H_INCLUDED
