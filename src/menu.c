#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "menu.h"
#include "game.h"



void mainMenu()
{
  int input;
  char player_name[21]={'\0'};
  bool end_of_program = false;

  //LOOP TO KEEP PLAYING
  do{
    //AFFICHAGE
    printf("\n---------------\n    Coinche\n---------------\n\n1 - Play\n2 - Leaderboard\n3 - Credits\n4 - Quit\n");

    //INPUTS
    scanf("%d", &input);
    while (input!=1 && input!=2 && input!=3 &&input!=4)
    {
      scanf("%d", &input);
    }
    printf("\n");

    if (input == 1)
    {
      askPlayerName(player_name);
      //LAUNCH GAME
      input = gameLoop();
      if (input == 1) // if player won
      {
        write2Leaderboard(player_name);
      }
    }
    else if (input == 2)
    {
      leaderboard();
    }
    else if (input == 3)
    {
      credits();
    }
  }while(!end_of_program && input != 4);
}


void askPlayerName(char player_name[])
{
  int c;

  printf("What is your name? %s\n", player_name);

  while ((c = getchar()) != '\n' && c != EOF) { } //Flush the input buffer
  fgets(player_name, 20, stdin);
}


void credits()
{
  printf("Game of coinche made as a project during our studies at the UTBM, P20 IFE.\n");
  printf("Made by Alexis BOULIGAND, Louis GIACINTI and Oscar DEWASMES.\n\n");
}


void leaderboard()
{
  FILE *fp;
  char current[21];
  int nb_lines=0;
  fp = fopen("Leaderboard.txt", "r");
  if (fp == NULL) perror ("Error opening file");

  //Count the number of lines in the file
  fgets(current, 22, fp);
  while(current[0]!='|')
  {
    nb_lines++;
    fgets(current, 60, fp);
  }
  //Reads the file
  char noms[nb_lines/2][21], scores[nb_lines/2][12];
  fseek(fp, 0, SEEK_SET);

  for (int i=0;i<nb_lines/2;i++)
  {
    fgets(noms[i], 255, (FILE*)fp);
    fgets(scores[i], 255, (FILE*)fp);
  }
  //Bubble sort the score and name arrays
  int nbPermutation = 1;
  int first_score = 0;
  int second_score = 0;
  char p[100] = ""; //p as permutation
  while (nbPermutation != 0)
  {
    nbPermutation = 0;

    for (int i=1; i<nb_lines/2; i++)
    {
      sscanf(scores[i-1], "%i", &first_score);
      sscanf(scores[i], "%i", &second_score);
      if (first_score < second_score)
      {
        strcpy(p, scores[i]);
        strcpy(scores[i], scores[i-1]);
        strcpy(scores[i-1], p);

        strcpy(p, noms[i]);
        strcpy(noms[i], noms[i-1]);
        strcpy(noms[i-1], p);

        nbPermutation += 1;
      }
    }
  }
  //Display the sorted leaderboard
  printf("\nLEADERBOARD:\n");
  for (int i=0; i<nb_lines/2;i++)
  {
    printf("%s",noms[i]);
    printf("  -%s",scores[i]);
  }

  fclose(fp);

}


void write2Leaderboard( char player_name[])
{
  FILE *fp;
  int file_length=1, name_length = strlen(player_name);
  int test, player_found = 0;
  char current;

  fp = fopen("Leaderboard.txt", "r");

  //measure file_length
  current = fgetc(fp);
  while (current!='|')
  {
    file_length++;
    current = fgetc(fp);
  }

  fseek(fp, 0, SEEK_SET); //back to position 0
  char file_content[file_length];

  //Read the file and store itt in file_content
  for (int i=0;i<file_length+1;i++)
  {
    file_content[i] = fgetc(fp);

    //Test if the name is in the file, to do so
    //check the player_name_length last characters read
    if (i>=name_length)
    {
      test = 0;
      for (int j=0; j<name_length; j++)
      {
        if (player_name[j]==file_content[i-name_length+j])
        {
          test ++;
        }
      }
      //If it found the name in the file, read score, score++
      if (test==name_length)
      {
        player_found = 1;
        char score[12];
        int j = 0, newscore;
        current = file_content[i];
        while (current!='\n')
        {
          score[j] = current;
          j++;
          current = fgetc(fp);
        }
        score[j] = '\0';

        newscore = atoi(score);
        newscore++;
        sprintf(score, "%d", newscore);


        //Writes score to file_content
        j = 0;
        while (score[j]!='\0')
        {
          file_content[i] = score[j];
          j++;
          i++;
        }
        file_content[i] = '\n';
      }
    }
  }
  fclose(fp);

  //Writes the file_content in to the file
  fp = fopen("leaderboard.txt", "w");
  int i=0;
  while (file_content[i]!='|')
  {
    fputc(file_content[i],fp);
    i++;
  }
  if (player_found==0)
  {
    fputs(player_name,fp);
    fputs("1\n",fp);
  }
  fputs("|\n",fp);

  fclose(fp);
}





//End of program
