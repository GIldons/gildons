//I_O.h
#ifndef I_O_H
#define I_O_H
#include "SDL/SDL.h"
#include "basic.h"

int init_serial();
int get_input(int , char * , int );
int send_output(int , char * , int );

#endif