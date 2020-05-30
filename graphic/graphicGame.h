#ifndef GRAPHICGAME_H_INCLUDED
#define GRAPHICGAME_H_INCLUDED

//Need all the player and AI cards
//The base of the graphical window
Card_t graphicPlayerCardChoice(Card_t player_hand[8], Card_t table_cards[4]);

void graphicDisplayPlayerCards(Card_t player_hand[8]);

void graphicDisplayTableCards(Card_t table_cards[4]);

void displayAfterPLayerChoicee(Card_t player_hand[8], Card_t table_cards[4]);
#endif // GRAPHICGAME_H_INCLUDED
