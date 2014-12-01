//basic.h
#ifndef basic_H
#define basic_H

#include <string>
#include "SDL/SDL.h"

typedef struct spot
{
	int fire_lvl;
	int * ext_count;
	int * onfire_count;
} Spot;

SDL_Surface *load_image(std::string, int alpha = 0);
void apply_surface( int , int , SDL_Surface* , SDL_Surface* , SDL_Rect* = NULL );

class FPS_Control
{
private:
	int start;
	int end;
	int FPS;
public:
	FPS_Control( int = 30 );
	void Start();
	void End();
};

const char* ftoa( float );
#endif
