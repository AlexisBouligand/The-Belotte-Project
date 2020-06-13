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

/*Function that start passes. It consists of a loop that will iterate trough player and AIs and ask them to choose a bet and a trump
  until 3 players skipped after the last bet.

  Arguments description :
  - all_player_and_AI_cards : array that contain player's and AIs hand
  - player_and_AI array : that contain each player and AIs
  - screen : the screen surface to display with SDL
  - background : screen's background

  This function return a char containing the trump color (or all trumps / no trumps) for the round*/
char startPasses(Card_t all_player_and_AI_cards[4][8], Player_t * player_and_AI, SDL_Surface *screen, SDL_Surface *background);


/*Function that start the round. it consists of a for loop that iterates 8 tricks where we will get the played card input for each
  Player and AIs and put them on the table. Then get the winner add points to it's point property, belote, xdder.

  Arguments description:
  - player_and_AI : array containing each player and AIs
  - all_player_and_AI_cards : array containing player's and AIs hand
  - trump : char that contain the trump color
  - screen : the screen surface to display with SDL
  - background : screen's background*/
void startRound(Player_t * player_and_AI, Card_t all_player_and_AI_cards[4][8], char trump, SDL_Surface *screen, SDL_Surface *background);


/*Function that shift the array containing player and AIs and sets the corresponding index first

  Arguments description :
  - player_and_AI : array containing each player and AI
  - index : index of the player / AI that we want to put at first*/
void changePlayerOrder(Player_t * player_and_AI, int index); //move all players to the left until the one selected is in first place

/*Function that initialize players and AI. It sets their ID and every other value to 0

  Arguments description:
  - player_and_AI : array containg each player and AI*/
void initializePlayers(Player_t * player_and_AI); //variables for every player to 0

//Called at the end of each round, adds up players points in to teams points.
//Respect contracts rules, capot, dix de der, belotte, rebelotte
void points_end_round(Player_t players[], int points_teams[]); //The points
#endif
