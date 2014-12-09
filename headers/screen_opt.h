//screen_opt.h
/*Game User/Screen Functions
 
# Project: FireFlight - ECE453
# Write by Raul Matheus Martins
# Sponsored by Plexu and CAPES - Brazil*/

#ifndef screen_opt_H
#define screen_opt_H
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "basic.h"

void screen_text(SDL_Surface **, int **, TTF_Font **);
void mouse_events(SDL_Event *, int **, Spot [][8], int , int*);
void show_table(Spot [][8], SDL_Surface *, SDL_Surface *, SDL_Surface *,SDL_Surface *);

#endif