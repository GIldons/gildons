//game_logic.h
#ifndef game_logic_H
#define game_logic_H

#include "SDL/SDL.h"
#include "basic.h"

void init_table(Spot [][10], int &);
void show_table(Spot [][10], SDL_Surface *, SDL_Surface *, SDL_Surface *);
void fire_spread(Spot [][10], int &);
void difc_table(int *, int);



#endif
