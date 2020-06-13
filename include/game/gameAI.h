#ifndef GAMEAI_H_INCLUDED
#define GAMEAI_H_INCLUDED

#include "game/variableManagement.h"
#include "game/game.h"

/*Function that compute the AI's Bet and Trump choice.
  It will checks which color has the largest number of "strong cards" (9, J, Q, K, X, 1)
  and bet from 82 to 102 if a color has 3 strong cards et 122 if it has more than 4 cards.

  Arguments description :
  - AI: pointer directed to the corresponding AI
        (we use a pointer because we change it's trump property)
  - max_bet : pointer to the current largest bet. (we alors change it's value)

  This function returns the value of max_bet to change the AI's bet*/
int getAIBet(Player_t *AI, Card_t *hand, int *max_bet);

/*Function that compute the AI's card choice to place on the table.
  It tries to use win the rick with the least valuable card of the AI's hand

  Arguments description :
  - table_cards : array containing the cards currently on the table
  - hand_length : the length of the AI's hand array
  - hand : array containing the playable cards of the AI's hand
  - index : index of the AI in the array containing the player and AIs
  - max_card_value : variable containing the value of the best trump card on the table
                     it is used in this case to check if there is a trump card on the table
                     (-1 means no, > -1 means yes)
  - trump : trump of the current round

  This function returns the card choosen by the AI*/
Card_t askAICard(Card_t *table_cards, int hand_length, Card_t *hand, int index, int max_card_value, char trump);

#endif
