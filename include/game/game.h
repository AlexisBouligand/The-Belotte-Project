#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "game/variableManagement.h"

typedef struct {
  //Player : 0, IA1 : 1, IA with the player : 2, IA3: 3
  int id;
  int bet;
  int points; //accumulated points in a round
  int belote; //max = 2, 1 : belote, 2 : rebelote
  int xdder; //dix de der
  char trump; //trump card chosen by the player
} Player_t;

//Loop for the rounds, counts the points scored by each teams and stop the game when
//a team reaches 701 points. If the user win, calls the function write2Leaderboard
//to register the user's win in the leaderboard
int gameLoop(SDL_Surface *screen, SDL_Surface *background, char *player_name);//The entire game

char startPasses(Card_t * deck_of_32_cards, Card_t all_player_and_AI_cards[4][8], Player_t * player_and_AI, SDL_Surface *screen, SDL_Surface *background); //function that start the passes and return the trump color

void startRound(Player_t * player_and_AI, Card_t all_player_and_AI_cards[4][8], char trump, SDL_Surface *screen, SDL_Surface *background); //start a round with 8 tricks

void changePlayerOrder(Player_t * player_and_AI, int index); //move all players to the left until the one selected is in first place

void initializePlayers(Player_t * player_and_AI); //variables for every player to 0

//Called at the end of each round, adds up players points in to teams points.
//Respect contracts rules, capot, dix de der, belotte, rebelotte
void points_end_round(Player_t players[], int points_teams[]); //The points
#endif
