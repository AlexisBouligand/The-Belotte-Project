#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED

#include "variableManagement.h"

int getBet(int * max); //ask player for a bet or skip, return the bet's values or 0 if skipped

char getTrump(); //ask player for a trump color

Card_t askCard(Card_t * player_hand, int hand_length); //ask player for a card to play

#endif
