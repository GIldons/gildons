//I_O.h
#ifndef I_O_H
#define I_O_H
#include "SDL/SDL.h"
#include "basic.h"

void turn_onoff(int);
int init_serial();
int get_input(int , char * , int );
int send_output(int , const void * , int );

#endif
