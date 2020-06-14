#ifndef LEADER_FILE_H_INCLUDED
#define LEADER_FILE_H_INCLUDED

//Called to read the leaderboard
/*Function called read the leaderboard file

  Argument description :
  - best_players : array of char that will be modified by the function with the
                  name of the three players with the mos wins
  - best_players_number : if there are less than 3 players in the leaderboard

  This function return nothing*/
void leaderboard(char best_players[3][30], int *best_players_number);
//Called to write the user's name to the Leaderboard
//if the user's name is already in the leaderboard, adds one to his win counter
//else, adds the user's name with a win counter set at one

/*Function called to write the user's name to the Leaderboard if the user's name
  is already in the leaderboard, adds one to his win counter else, adds the user's
  name with a win counter set at one

  Argument description :
  - player_name : array of char containing the user's name

  This function return nothing*/
void write2Leaderboard(char player_name[]);

#endif
