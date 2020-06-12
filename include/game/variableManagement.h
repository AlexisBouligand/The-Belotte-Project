#ifndef VARIABLEMANAGEMENT_H_INCLUDED
#define VARIABLEMANAGEMENT_H_INCLUDED
#include "graphics/sprite.h"


//This is the structure that defines a card
typedef struct {

        char name;
        char color;

        //The card can be considered as a button
        Sprite_t card_sprite;

        //The name needed to load the .bmp
        char image_name[15];

        //Determine his power
        int value;
        int trump_card_value;

        //The number of points it scores
        int point;
        int trump_card_point;
        int all_trumps_point;
        int no_trumps_point;

} Card_t;


//This function initialize all the 32 cards of the game
//Need a table of 32 Card_t
void initializeCardGame(Card_t card_game[32]);

//This function deal the cards
//Need the reference array of all the cards and the hand of the player and AI
void randomDraw(Card_t all_player_and_AI_cards[4][8], Card_t card_game[32]);

//this function display the hand of the player
//Need a player hand of Card_t
void displayHand(Card_t player_hand[8]);

//Display the cards at the center of the table
//Need the cards that have been played this turn
//first_player can take 4 value ; Player : 0, IA1 : 1, IA with the player : 2, IA3: 3
void displayTableCards(Card_t table_cards[4]);

//Shift the cards to the left, from the card_to_remove
//Need The size of the array, a Card_t array and the number of the card_to_remove in the array
void shiftCards(int size_of_array, Card_t *array_of_cards, int card_to_remove);


#endif // VARIABLEMANAGEMENT_H_INCLUDED
