//I_O.h
#ifndef I_O_H
#define I_O_H
#include "SDL/SDL.h"
#include "basic.h"
#include "I_O.h"

void turn_onoff(int);
int init_serial(int *);
int get_input(int , char *);
int send_output(int , char *);
// void teste(Spot table[][8], int);
void send_tile(Spot table[][8], int , int );
void read_heli(Spot table[][8], int, int ** );
void openBluetooh(int);

#endif
