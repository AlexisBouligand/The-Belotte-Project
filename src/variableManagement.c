#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "variableManagement.h"

void initializeCardGame(Card_t card_game[32])
{
    //The variables needed to initialize
    char name[9] = "789JQKX1";
    //When the color is equal to 0, the card no longer exist
    char color[5] = "HDCS";


    int value[8] = {1,2,3,4,5,6,7,8};
    int trump_card_value[8] = {1,2,7,8,3,4,5,6};

    int point[8] = {0,0,0,2,3,4,10,11};
    int trump_card_point[8] = {0,0,3,4,10,11,14,20};
    int all_trump_point[8] = {0,0,1,3,5,6,9,14};
    int no_trumps_point[8] = {0,0,0,2,3,4,10,19};

    int i = 0;
    int j = 0;
    //We give to each card his caracteristics in this loop
    for(int k = 0 ; k<32 ; k++)
    {
        j = k%8;//Needed because all the variable for initialization have only 8 cases
        if(j ==0 && k!=0)//Needed for the colors, which have only a 4 cases array
        {
            i++;
        }

        card_game[k].name = name[j];
        card_game[k].color = color[i];

        card_game[k].value = value[j];
        card_game[k].trump_card_value = trump_card_value[j];

        card_game[k].point = point[j];
        card_game[k].trump_card_point = trump_card_point[j];
        card_game[k].all_trumps_point = all_trump_point[j];
        card_game[k].no_trumps_point = no_trumps_point[j];
    }
}



void randomDraw(Card_t all_player_and_AI_cards[4][8], Card_t card_game[32])
{
    Card_t *card_game_copy = card_game;
    int number_of_remaining_cards = 32;
    int random_number = 0;


    for(int i = 0 ; i<4 ; i++)
    {

        for(int j = 0 ; j<8 ; j++)
        {
            //Draw a random number between 0 and remaining_number_of_cards for a ra,ndom card and put the card into the hand of a player
            srand(time(0));
            random_number = rand()%number_of_remaining_cards;
            all_player_and_AI_cards[i][j] = card_game_copy[random_number];

            //We shift the cards on the left
            shiftCards(number_of_remaining_cards, card_game_copy, random_number);
            number_of_remaining_cards--;
        }
    }
}



void displayHand(Card_t player_hand[8])
{
    for(int i = 0; i<8 ; i++)
    {
        if(player_hand[i].color != 0)
        {
        printf("| %c%c |", player_hand[i].color, player_hand[i].name);
        }
    }

}


void displayTableCards(Card_t table_cards[4])
{
    printf("\n");
    //We display the car, if it exists( if its color !=0)
    for(int i = 0 ; i<4 ; i++)
    {
        if(table_cards[i].color != 0)
        {
            printf("%d |%c%c|\n",i, table_cards[i].color, table_cards[i].name);
        }
    }
}


void shiftCards(int size_of_array, Card_t *array_of_cards, int card_to_remove)
{
    for(int i = card_to_remove ; i<size_of_array ; i++)
    {
        array_of_cards[i] = array_of_cards[i+1];
    }
    array_of_cards[size_of_array-1].color = 0;
}
