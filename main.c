#include "game.h"
#include "variableManagement.h"



int main(int argc, char** argv )
{

  char trump;
  //The reference array
  Card_t deck_of_32_cards[32];

  //The array which contain all the plauer and AI hands
  Card_t all_player_and_AI_cards[4][8];

  //array containing player/AI
  Player_t player_and_AI[4];

  initializeCardGame(deck_of_32_cards);

  //boucle

  randomDraw(all_player_and_AI_cards, deck_of_32_cards);

  initializePlayers(player_and_AI);

  //changePlayerOrder( player_and_AI, compteur de tours); pour chacun son tour

trump = startPasses(deck_of_32_cards, all_player_and_AI_cards, player_and_AI)   ;

  startRound(player_and_AI, all_player_and_AI_cards, trump);

  //fonctions pour calculer les points et les mettre quelque part



  //fin de boucle

  return 0;
}
