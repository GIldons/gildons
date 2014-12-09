//game_logic.h
/*Game Logic Functions
 
# Project: FireFlight - ECE453
# Write by Raul Matheus Martins
# Sponsored by Plexu and CAPES - Brazil*/


#ifndef game_logic_H
#define game_logic_H

#include "SDL/SDL.h"
#include "basic.h"

void init_table(Spot [][8], int **);
void fire_spread(Spot [][8], int **);
void difc_table(int *, int);



#endif
