#ifndef GRAPHICPASSES_H_INCLUDED
#define GRAPHICPASSES_H_INCLUDED
#include "graphics/sprite.h"
#include "game/variableManagement.h"
#include <SDL/SDL_ttf.h>
#include "game/game.h"
///All the following functions need the creen surface and/or the background

//Ask for the maximum bet until now, the player hand(for display) and all the player
//Get with buttons the value and the trump of the bet
//Return the bet value from the player
int graphicGetBet(int *max, Card_t *player_hand, Player_t *player_and_AI, SDL_Surface *screen, SDL_Surface *background);

//Ask the player for the trump he want to bet
//Return the player bet trump from the player
char graphicGetTrump(SDL_Surface *screen, SDL_Surface *background);

//Ask for all the player, the font to use to display and the color of the font
//Display the AI bets
void displayAIBet(Player_t *player_an_AI, TTF_Font *font, SDL_Color color, SDL_Surface *screen);

//Initialize the sprite and the positions of the buttons
//Need an array of button
void betButtonInitialization(Sprite_t betButton[4]);
void trumpButtonInitialization(Sprite_t trump_button[6]);

#endif // GRAPHICPASSES_H_INCLUDED
