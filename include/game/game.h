#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "game/variableManagement.h"


/*Structure that contains player and AI properties.

  Properties description:
  - id : id of the player / AI.
         player / AIs with even ids are in the first team and odd ids in the other
  - bet : player's / AI's bet during passes
  - points : points accumulated during the round
  - belote : value that determines if the player / AI has done a belote / rebelote
             belote = 1 corresponds to a belote
             belote = 2 corresponds to a rebelote
  - xdder : boolean used to check if the player / AI has done a dix de der
  - trump : the trump chosen by the player / AI during the passes*/
typedef struct {
  //Player : 0, IA1 : 1, IA with the player : 2, IA3: 3
  int id;
  int bet;
  int points;
  int belote;
  int xdder;
  char trump;
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

/*Function that checks if the selected card can be played during a trick

  Arguments description:
  - first_card : the first card placed one the table
  - first_id : the id of the first player that have played
  - player_card : the card selected
  - player_id : the ID of the player / AI who choosed the card
  - player_hand : array containing player's hand
  - hand_length : the length of the player_hand array
  - max_card_value : the value of the best trump card actually on the table
  - trump : the trump of the round

  This function returns a boolean if the player can player the selected card or not*/
int canPlayCard(Card_t first_card, int first_id, Card_t player_card, int player_id, Card_t *player_hand, int hand_length, int max_card_value, char trump);


/*Function that shift the array containing player and AIs and sets the corresponding index first

  Arguments description :
  - player_and_AI : array containing each player and AI
  - index : index of the player / AI that we want to put at first*/
void changePlayerOrder(Player_t * player_and_AI, int index); //move all players to the left until the one selected is in first place

/*Function that initialize players and AI. It sets their ID and every other value to 0

  Arguments description:
  - player_and_AI : array containg each player and AI*/
void initializePlayers(Player_t * player_and_AI);

//Called at the end of each round, adds up players points in to teams points.
//Respect contracts rules, capot, dix de der, belotte, rebelotte
void points_end_round(Player_t players[], int points_teams[]); //The points
#endif
