//I_O.h
/*I_O Functions
 
# Project: FireFlight - ECE453
# Write by Raul Matheus Martins
# Sponsored by Plexu and CAPES - Brazil*/


#ifndef I_O_H
#define I_O_H
#include "SDL/SDL.h"
#include "basic.h"
#include "I_O.h"

void turn_onoff(int);
int init_serial(int *);
int send_output(int , char *);
void send_tile(Spot table[][8], int , int );
void read_heli(Spot table[][8], int, int ** );
void openBluetooh(int);

#endif
