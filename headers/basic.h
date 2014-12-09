//basic.h
/*Game Basic Functions
 
# Project: FireFlight - ECE453
# Write by Raul Matheus Martins
# Sponsored by Plexu and CAPES - Brazil*/


#ifndef basic_H
#define basic_H

#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

typedef struct spot
{
	int fire_lvl;
	int * ext_count;
	int * onfire_count;
	unsigned int ID;
	int LED_ID;
} Spot;

SDL_Surface *load_image(const char *, int alpha);
void apply_surface( int , int , SDL_Surface* , SDL_Surface* , SDL_Rect*);// = NULL );
int fps(int *);
int timer(int *, int );
int load(SDL_Surface **, TTF_Font **);
#endif
