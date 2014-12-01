//screen.h
#ifndef screen_H
#define screen_H
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "basic.h"

SDL_Surface *make_screen();
SDL_Surface *display();
void closeWindow();
void screen_clean();
int update_display(Sint16 = 0, Sint16 = 0);
int apply_screen(SDL_Surface **, Spot [][10], int **, TTF_Font **);
//TTF_Font *sourceFont();

#endif
