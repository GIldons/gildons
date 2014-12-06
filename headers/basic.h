//basic.h
#ifndef basic_H
#define basic_H

#include <string.h>
#include "SDL/SDL.h"

typedef struct spot
{
	int fire_lvl;
	int * ext_count;
	int * onfire_count;
	int ID;
} Spot;

SDL_Surface *load_image(const char *, int alpha = 0);
void apply_surface( int , int , SDL_Surface* , SDL_Surface* , SDL_Rect* = NULL );
int fps(int *);
int timer(int *, int );
#endif
