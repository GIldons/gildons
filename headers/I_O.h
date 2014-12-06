//I_O.h
#ifndef I_O_H
#define I_O_H
#include "SDL/SDL.h"
#include "basic.h"
#include "I_O.h"

void turn_onoff(int);
int init_serial();
int get_input(int , const char * , int );
int send_output(int , const char *);
void teste(Spot table[][8], int);
#endif
