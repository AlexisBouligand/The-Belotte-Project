#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "variableManagement.h"

typedef struct {
  //Player : 0, IA1 : 1, IA with the player : 2, IA3: 3
  int id;
  int bet;
  int points; //accumulated points in a round
  int belote; //max = 2, 1 : belote, 2 : rebelote
  int xdder; //dix de der
  char trump; //trump card chosed by the player
} Player_t;

int gameLoop();//game loop

char startPasses(Card_t all_player_and_AI_cards[4][8], Player_t * player_and_AI); //function that start the passes and return the trump color

void startRound(Player_t * player_and_AI, Card_t all_player_and_AI_cards[4][8], char trump); //start a round with 8 tricks

void changePlayerOrder(Player_t * player_and_AI, int index); //move all players to the left until the one selected is in first place

void initializePlayers(Player_t * player_and_AI); //variables for every player to 0

void points_end_round(Player_t players[], int points_teams[]);


#endif
