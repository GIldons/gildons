//screen_opt.h
#ifndef screen_opt_H
#define screen_opt_H
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "basic.h"

void screen_text(SDL_Surface **, int **, TTF_Font **);
void mouse_events(SDL_Event &, int **);

#endif