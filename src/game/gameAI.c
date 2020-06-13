#include <string.h>
#include <stdio.h>
#include "game/variableManagement.h"
#include "game/game.h"
#include "game/gameAI.h"


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


  } else return -1; //skip (-1 to be showed in the graphic part)

  (*AI).trump = best_color; //set trump
  return *max_bet;

}




Card_t askAICard(Card_t *table_cards, int hand_length, Card_t *hand, int index, int max_card_value, char trump) {
  int i; //counter
  int current_winner_card_value = -1; //current winner's card value (if stays at -1, the AI will be the first)
  int has_trump = 0; //if the AI has a trump card

  //best AI's card to play
  Card_t best_card = {.value = 100, .trump_card_value = 100}; //setting to high value to take the lowest card possible
  //worst AI's card to play
  Card_t worst_card = {.value = 100, .trump_card_value = 100};

  for(i = 0; i < index; i++)
  {
    // max_card_value > -1 => if there is already a trump card ingame
    if(max_card_value > -1 && table_cards[i].trump_card_value > current_winner_card_value)
    {
      current_winner_card_value = table_cards[i].trump_card_value;

    } else if(max_card_value == -1 && table_cards[i].value > current_winner_card_value)
    {
      current_winner_card_value = table_cards[i].value;
    }
  }

  for (i = 0; i < hand_length; i++)
  {
    if (hand[i].color == trump || trump == 'A')
    {
      has_trump = 1;
      break;
    }
  }

  for( i = 0; i < hand_length; i++)
  {
    //if the AI has trump and must use it
    if(has_trump && (max_card_value > -1 || trump == 'A'))
    {
      if(hand[i].trump_card_value > current_winner_card_value && hand[i].trump_card_value < best_card.trump_card_value)
      {
        best_card = hand[i];
      }
      if(hand[i].trump_card_value < worst_card.trump_card_value)
      {
        worst_card = hand[i];
      }
    }
    //if the AI don't have any trump but there is a trump card on the table
    else if(!has_trump && max_card_value > -1)
    {
      if(hand[i].value < worst_card.value)
      {
        worst_card = hand[i];
      }
    }
    //if there is no trump cards on the table and the current card is not a trump
    else if (max_card_value < 0 && hand[i].color != trump)
    {
      if(hand[i].value > current_winner_card_value && hand[i].value < best_card.value)
      {
        best_card = hand[i];
      }
      if(hand[i].value < worst_card.value)
      {
        worst_card = hand[i];
      }
    }
  }

  //if no cards are better than the current winner's card
  if(best_card.value == 100)
  {
    //if it has to use a trump card
    if(max_card_value > -1 || trump == 'A')
    {
      return worst_card;
    }
    //if there was no trump cards and no normal cards could be better we take the lowest AI's trump card.
    else if(max_card_value < 0)
    {
      for(i = 0; i < hand_length; i++)
      {
        if(hand[i].color == trump && hand[i].trump_card_value < best_card.trump_card_value)
        {
          best_card = hand[i];
        }
      }

      //if there is still no best card
      if(best_card.value == 100)
      {
        return worst_card;
      }

    }
  }

  return best_card;

}
