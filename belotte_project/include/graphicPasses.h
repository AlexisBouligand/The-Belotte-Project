#ifndef GRAPHICPASSES_H_INCLUDED
#define GRAPHICPASSES_H_INCLUDED
#include "../include/sprite.h"
#include "../include/variableManagement.h"
#include <SDL/SDL_ttf.h>
#include "../include/game.h"

//The window initialization
void initializePassWindow();

//Ask for the maximum bet until now, the player hand(for display) and all the player
//Return the bet value from the player
int graphicGetBet(int *max, Card_t *player_hand, Player_t *player_and_AI);
//Return the player bet trump from the player
char graphicGetTrump();

//Ask for all the player, the font to use to display and the color of the font
//Display the AI bets
void displayAIBet(Player_t *player_an_AI, TTF_Font *font, SDL_Color color);

//Initialize the sprite and the positions of the button
void betButtonInitialization(Sprite_t betButton[4]);
void trumpButtonInitialization(Sprite_t trump_button[6]);

#endif // GRAPHICPASSES_H_INCLUDED
