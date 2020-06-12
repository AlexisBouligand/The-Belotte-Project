#include <stdio.h>
#include <ctype.h>
#include "gameInput.h"
#include "variableManagement.h"

char getTrump()
{
  char trump = 'X';
  char possibilities[7] = "DCSHNA"; //all trumps possibilities with all and no trumps
  char input; //player' input
  int i; //counter


  do
  {
    printf("\nChoose a trump : (D/C/S/H/N/A)\n");
    input = toupper(getchar());

    fflush(stdin); //clearing buffer

    //checks if the input matches one of the possibilities
    for (i = 0; i < 6; i++)
    {
      if(possibilities[i] == input)
      {
        trump = input;
      }
    }


  } while(trump == 'X');

  return trump;
}




int getBet(int *max)
{
  char input[10];
  int value;

  do
  {
    printf("\n\nWrite your bet (min : 82, bigger than the last one, 10 by 10, max : 152).\nElse S to skip.\n");

    fgets(input, 10, stdin); //gets the input in char form

    fflush(stdin); //clearing buffer

    if (toupper(input[0]) == 'S') //skip if the value is 's' or 'S'
    {
      return 0;
    }

    sscanf(input, "%i", &value); //parse the input to an integer

    if ((value - 2) % 10 == 0 && value >= 82 && value > *max && value <= 152)
    {
      *max = value;
    }
    else
    {
      value = 0;
    }

  } while(value == 0); //do while the value is incorrect

  return value;
}


Card_t askCard(Card_t * player_hand, int hand_length) {
  int not_in_hand = 1; //variable to check if the card is in the player's hand
  int i; //counter
  char card_letters[2]; //will contain the input of the user {color, name}
  Card_t played_card; //will contain the chosed card

  do
  {
    printf("Choose a card to play : ");
    displayHand(player_hand);
    putchar('\n');

    scanf("%c%c", &card_letters[0], &card_letters[1]);//getting user input
    fflush(stdin); //clearing buffer

    for (i = 0; i < hand_length; i++) //checking for each card if it is in the player's hand
    {
      if (player_hand[i].color == card_letters[0] && player_hand[i].name == card_letters[1])
      {
        played_card = player_hand[i];
        not_in_hand = 0;
        break;
      }
    }

  } while (not_in_hand); //loop while the card is incorrect.


  return played_card;

}
