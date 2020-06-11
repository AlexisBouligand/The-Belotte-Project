#ifndef GAMEAI_H_INCLUDED
#define GAMEAI_H_INCLUDED

#include "../include/variableManagement.h"
#include "../include/game.h"

//function that gets AI bet and trump
int getAIBet(Player_t *AI, Card_t *hand, int *max_bet);

//function that get the card that the AI play according to playable cards
Card_t askAICard(Card_t *table_cards, int hand_length, Card_t *hand, int index, int max_card_value, char trump);

#endif
