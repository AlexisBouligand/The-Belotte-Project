#include <string.h>
#include "variableManagement.h"
#include "game.h"
#include "gameAI.h"

#include <stdio.h>

int getAIBet(Player_t *AI, Card_t *hand, int *max_bet)
{
  char colors[] = "DCSH"; //colors name
  char strong_card[] = "9JQKX1"; //strong cards name
  int colors_strength[4]= {0}; //a strong_card equals +1 strength
  int best_color = 0; //color that have the largest number of strong cards
  int best_color_strength = 0;
  int i;
  int j;

  for(i = 0; i < 4; i++) //for each color
  {
    for(j = 0; j < 8; j++) //for each card
    {

      if(hand[j].color == colors[i])
      {
        char name[] = "0";
        name[0] = hand[j].name; //we have to convert it to a string for strstr to work.

        if(strstr(strong_card, name)) //checks if card's name is a strong_card name
        {
          colors_strength[i]++;
        }
      }
    }
    if(colors_strength[i] > best_color_strength)
    {
      best_color = colors[i];
      best_color_strength = colors_strength[i];
    }
  }

  if(*max_bet < 122 && best_color_strength>=4) //if more than 4 strong cards
  {
    *max_bet = 122;

  } else if(*max_bet < 102 && best_color_strength == 3) //if 3 strong cards
  {
    if(*max_bet == 0)
    {
      *max_bet = 82;
    } else {
      *max_bet += 10;
    }


  } else return 0; //skip

  (*AI).trump = best_color; //set trump
  return *max_bet;

}




Card_t askAICard(Card_t *table_cards, int hand_length, Card_t *hand, int index, int max_card_value, char trump) {
  int i; //counter
  int current_winner_index = 0; //index of the current winner if index%2 == current_winner_index%2 they are in the same team
  int current_winner_card_value;
  Card_t best_card; //best AI's card
  Card_t worst_card; //worst AI's card

  current_winner_card_value = -1;

  if(max_card_value>-1) //if there are trump cards on the table
  {
    best_card.trump_card_value = -1; //always less than cards values
    worst_card.trump_card_value = 50; //arbitrary chosen number (always bigger than cards values)
  } else {
    best_card.value = -1;
    worst_card.value = 50;
  }

  for(i = 0; i < hand_length; i++)
  {
    if(max_card_value > -1)
    {
      if(hand[i].trump_card_value > best_card.trump_card_value)
      {
        best_card = hand[i];
      }
      if(hand[i].trump_card_value < worst_card.trump_card_value)
      {
        worst_card = hand[i];
      }
    } else {
      if(hand[i].value > best_card.value)
      {
        best_card = hand[i];
      }
      if(hand[i].value < worst_card.value)
      {
        worst_card = hand[i];
      }
    }
  }

  for(i = 0; i < index; i++)
  {
    if(max_card_value > -1 && table_cards[i].trump_card_value > current_winner_card_value)
    {
      current_winner_card_value = table_cards[i].trump_card_value;
      current_winner_index = i;

    } else if(max_card_value == -1 && table_cards[i].value > current_winner_card_value)
    {
      current_winner_card_value = table_cards[i].value;
      current_winner_index = i;
    }
  }


  if(current_winner_index%2 == index%2) //if current winner is a teammate or the AI itself
  {
    return best_card;
  } else if(best_card.trump_card_value > current_winner_card_value || best_card.value > current_winner_card_value) //if better card than current_winner
  {
    return best_card;
  }

  return worst_card;

}
