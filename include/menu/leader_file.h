#ifndef LEADER_FILE_H_INCLUDED
#define LEADER_FILE_H_INCLUDED

//Called to read the leaderboard
void leaderboard(char best_players[3][30]);
//Called to write the user's name to the Leaderboard
//if the user's name is already in the leaderboard, adds one to his win counter
//else, adds the user's name with a win counter set at one
void write2Leaderboard(char player_name[]);

#endif
