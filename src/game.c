#include <stdio.h>
#include "game.h"
#include "gameInput.h"
#include "gameAI.h"
#include "variableManagement.h"


int gameLoop()
{
  //Teams points
  int points_teams[2] = { 0,0 };

  //The reference array
  Card_t deck_of_32_cards[32];

  //The array which contain all the plauer and AI hands
  Card_t all_player_and_AI_cards[4][8];

  //array containing player/AI
  Player_t player_and_AI[4];

  //trump
  char trump;

  //Number of round
  int number_of_round=0;

  while (points_teams[0] < 701 && points_teams[1] < 701)
  {
    initializeCardGame(deck_of_32_cards);

    randomDraw(all_player_and_AI_cards, deck_of_32_cards);

    initializePlayers(player_and_AI);

    changePlayerOrder( player_and_AI, number_of_round); //to set the first player

    trump = startPasses(all_player_and_AI_cards, player_and_AI);

    printf("\nEnd of passes\n");

    startRound(player_and_AI, all_player_and_AI_cards, trump);

    //fonctions pour calculer les points et les mettre quelque part
    points_end_round(player_and_AI, points_teams);
    printf("\nTrick results:\nYour team : %d,\nOther team : %d\n",points_teams[0],points_teams[1]);

    number_of_round ++;
    printf("ended round %d\n",number_of_round);
  }

  //fin de boucle
  if (points_teams[0] > points_teams[1])
  {
      //Player won
      return 1;
  }
  return 0;
}




void initializePlayers(Player_t * player_and_AI)
{
  int i;

  for(i = 0; i < 4; i++)
  {
    player_and_AI[i].id = i;
    player_and_AI[i].bet = 0;
    player_and_AI[i].points = 0;
    player_and_AI[i].belote = 0;
    player_and_AI[i].xdder = 0;
    player_and_AI[i].trump = 0;
  }

}


int canPlayCard(Card_t first_card, int first_id, Card_t player_card, int player_id,
                Card_t * player_hand, int hand_length, int max_card_value, char trump)
{
  int has_color = 0; //if the player has the color asked
  int has_trump = 0; //if the player has a trump card
  int has_better_trump = 0; //if the player has a better trump card than best on the table
  int is_same_team = 0; //if the first player and the current one are in the same team
  int i; //counter

  for (i = 0; i < hand_length; i++) //checking has_color and has_trump in the player's hand
  {
    if (player_hand[i].color == first_card.color) has_color = 1;
    if (player_hand[i].color == trump || trump == 'A')
    {
      has_trump = 1;
      if(player_hand[i].trump_card_value > max_card_value)
      {
        has_better_trump = 1;
      }
    }
    if (has_color && has_trump) break;
  }

  if(first_id % 2 == player_id % 2) is_same_team = 1; //if players ids are even (same team), id % 2 = 0, else id % 2 = 1

  //check each possible case
  if(first_card.color == player_card.color)
  {
    return 1;
  } else if (is_same_team && !has_color)
  {
    return 1;
  } else if (!has_color && (player_card.color == trump || trump == 'A') &&
              player_card.trump_card_value > max_card_value)
  {
    return 1;
  } else if (!has_color && !has_better_trump)
  {
    return 1;
  } else return 0;
}



int getWinner(Player_t * player_and_AI, Card_t * table_cards, char trump, int trick_number)
{
  int are_trump = 0; //is there are trump cards on the table
  int winner_index = 0; //index of the winner in player_and_AI array
  int max_value = 0; //card with the max value
  int trick_points = 0; //the trick's points
  int i; //counter

  for(i = 0; i < 4; i++) //for each card on the table, checks if there are trump cards and set the trick's value
  {
    if(trump == table_cards[i].color)
    {
      are_trump = 1;
      trick_points += table_cards[i].trump_card_point;
    }
    else if(trump == 'A') //all trumps
    {
      are_trump = 1;
      trick_points += table_cards[i].all_trumps_point;
    }
    else if(trump == 'N') //no trumps
    {
      trick_points += table_cards[i].no_trumps_point;
    }
    else
    {
      trick_points += table_cards[i].point;
    }
  }

  for(i = 0; i < 4; i++) //get the card with the maximum value and the winner's index
  {
    if(are_trump && (trump == table_cards[i].color || trump == 'A') &&
                    table_cards[i].trump_card_value > max_value) //checks only trump cards
    {
      max_value = table_cards[i].trump_card_value;
      winner_index = i;
    }
    else if (!are_trump && table_cards[i].value > max_value)
    {
      max_value = table_cards[i].value;
      winner_index = i;
    }
  }

  player_and_AI[winner_index].points += trick_points; //adding trick's point in winner points

  if(trick_number == 7) //if this is the last trick
  {
    player_and_AI[winner_index].xdder +=1;
  }

  return winner_index;

}




void changePlayerOrder(Player_t * player_and_AI, int index) //index of the player we want to move in first place
{
  Player_t temp_player;
  int i;
  int j;

  for(i = 0; i < index; i++) //move all players in the left of the array until the first is the one selected
  {
    temp_player = player_and_AI[0];
    for(j = 0; j < 3; j++)
    {
      player_and_AI[j] = player_and_AI[j+1];
    }
    player_and_AI[3] = temp_player;
  }
}



char startPasses(Card_t all_player_and_AI_cards[4][8], Player_t * player_and_AI)
{
  char round_trump;
  int has_someone_bet = 0; //if someone bet
  int skip_counter = 0; //number of players that have skipped in a row
  int max_bet = 0; //maximum bet
  int i; //counter

  do
  {
    for(i = 0; i < 4; i++) //for each player
    {


      if (player_and_AI[i].id == 0)
      {
        printf("\nYour hand:\n");
        displayHand(all_player_and_AI_cards[i]);

        player_and_AI[i].bet = getBet(&max_bet); //get player input for bet
      } else {

        printf("\nAI %i :\n", player_and_AI[i].id);
        player_and_AI[i].bet = getAIBet(&player_and_AI[i], all_player_and_AI_cards[i], &max_bet); //get AI's bet and also trump.
      }


      if (player_and_AI[i].bet > 0) //returned 0 means player has skipped
      {
        if(max_bet < 162)
        {
          printf("Bet : %i\n", player_and_AI[i].bet);
        } else {
          printf("Bet : Capot\n");
        }


        if(player_and_AI[i].id == 0)
        {
          round_trump = getTrump(); //get the color wanted to be trump
          player_and_AI[i].trump = round_trump;

        } else if(player_and_AI[i].trump != 0) //if AI have not skipped
        {
          round_trump = player_and_AI[i].trump;
        }

        printf("Trump : %c\n", round_trump);

        if(max_bet == 162) return round_trump; //If bet is the maximum the loop is not necessary anymore
        skip_counter = 0; //reset the counter if someone bet
        has_someone_bet = 1;

      } else
      {
        printf("Skip\n");
        skip_counter += 1;
      }
      if((skip_counter == 3 && has_someone_bet == 1)) break;
    }
  } while(skip_counter < 3 || !has_someone_bet); //checks if everyone skipped, or 3 in a row after someone bet

  return round_trump;

}




void startRound(Player_t * player_and_AI, Card_t all_player_and_AI_cards[4][8], char trump)
{
  Card_t table_cards[4]; //cards placed in each trick
  Card_t played_card; //variable that contain the current card
  int winner_index; //winner's index in player_and_AI
  int max_card_value; //contain the value of the highest trump card in the trick (used if another player play a trump card)
  int i; //counters
  int j;

  for (i = 0; i < 8; i++) //start of tricks
  {

    max_card_value = -1;

    for(j = 0; j < 4; j++)
    {
      table_cards[j].color = 0; //disabling cards from the table
    }

    for(j = 0; j < 4; j++) //for each player
    {

      int can_play_card = 0; //variable to check if the player can use the card he chosed
      int card_index;
      Card_t *current_hand; //current player's hand

      current_hand = all_player_and_AI_cards[player_and_AI[j].id];

      if(player_and_AI[j].id == 0) //if player is not an AI
      {
        printf("\nYour turn :\n");
        do
        {
          /*In arrays all_player_and_AI_cards and last_played_cards_colors, indexes do not match with player_and_AI indexes.
          It matches player_and_AI[j].id, that is because we change the order in player_and_AI.*/
          played_card = askCard(current_hand, 8-i); //asking the player to choose a card
          if(j > 0)
          {
            can_play_card = canPlayCard(table_cards[0], player_and_AI[0].id, played_card, player_and_AI[j].id,
                                        current_hand, 8-i, max_card_value, trump);
                                        //checks if the player can use the card he chosed

          } else can_play_card = 1;

        } while(!can_play_card); //loop until the player can play the card

      } else { //if AI

        printf("\nAI %i :\n", player_and_AI[j].id);
        Card_t playable_cards[8]; //array that contain playable cards
        int playable_cards_length = 0;
        int k; //counter

        if(j > 0) //if not first player
        {

          for (k = 0; k < 8 - i; k++)
          {
            if(canPlayCard(table_cards[0], player_and_AI[0].id, current_hand[k], player_and_AI[j].id,
                           current_hand, 8-i, max_card_value, trump))
            {
               playable_cards[playable_cards_length] = current_hand[k];
               playable_cards_length++;
            }
          }
          played_card = askAICard(table_cards, playable_cards_length, playable_cards, j, max_card_value, trump);

        } else {
          played_card = askAICard(table_cards, 8-i, current_hand, j, max_card_value, trump);
        }
      }

      if((played_card.color == trump || trump == 'A') && played_card.trump_card_value > max_card_value)
      {
        max_card_value = played_card.trump_card_value;
      }

      table_cards[j] = played_card; //adding the card on the table

      for (card_index = 0; card_index < 8-i; card_index++)
      {
        Card_t card = all_player_and_AI_cards[player_and_AI[j].id][card_index]; //getting the played card index in player's hand.

        if(card.color == played_card.color && card.name == played_card.name)
        {
          break; //if it matches we stop increasing card_index
        }
      }

      if((played_card.color == trump || trump == 'A') && (played_card.name == 'K' || played_card.name == 'Q')) //check if belote/rebelote
      {
        player_and_AI[j].belote += 1;
        if(player_and_AI[j].belote % 2 == 1)
        {
          printf("Belote\n");
        } else printf("Rebelote\n");
      }

      shiftCards(8-i, all_player_and_AI_cards[player_and_AI[j].id], card_index); //we remove the card in the player's hand
      displayTableCards(table_cards); //displaying table cards.


    }
    winner_index = getWinner(player_and_AI, table_cards, trump, i);

    changePlayerOrder(player_and_AI, winner_index);

    printf("\nEnd of the trick.\n");

  }


  for (j = 0; j < 4; j++) //remove belote counter if there was a belote but no rebelote
  {
    if(player_and_AI[j].belote % 2 == 1)
    {
      player_and_AI[j].belote--;
    }
  }

}



void points_end_round(Player_t players[], int points_teams[])
{
  int bet = 0;
  int team_bet_id;
  int i;
  for (i = 0; i < 4; i++)
  {
    if(players[i].bet > bet)
    {
      bet = players[i].bet;
      team_bet_id = i % 2;
    }
  }

  for (i=0; i<2; i++)
  {
      if (i==team_bet_id)
      {
        if (players[i].points + players[i+2].points >= bet)
        {
          //Won theire bet
          points_teams[players[i].id%2] += bet + players[i].points + players[i+2].points;
        }
      }

      else if (players[(i+1)%2].points + players[(i+1)%2+2].points + players[(i+1)%2].xdder * 10 + players[(i+1)%2+2].xdder * 10 >= bet) //(i+1)%2 => the other team
        {
          points_teams[players[i].id%2] += players[i].points + players[i+2].points;
        }
        else
        {
          points_teams[players[i].id%2] += 162 + players[i].points + players[i+2].points;
        }


      if (players[i].points + players[i+2].points + players[i].xdder * 10 + players[i+2].xdder * 10 == 162 && i == team_bet_id && bet == 162)
      {
        points_teams[players[i].id%2] += 100;
      }
      else
      {
        points_teams[players[i].id%2] += players[i].xdder * 10 + players[i+2].xdder * 10;
      }
      points_teams[players[i].id%2] += players[i].belote/2 * 20 + players[i+2].belote/2 * 20;
  }

}
