//game_logic.h
#ifndef game_logic_H
#define game_logic_H

#include "SDL/SDL.h"
#include "basic.h"

void init_table(Spot [][8], int *);
void fire_spread(Spot [][8], int *);
void difc_table(int *, int);



#endif
