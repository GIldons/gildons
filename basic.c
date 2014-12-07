#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string.h>
// #include <sstream>
#include "headers/basic.h"
#include "headers/screen.h"

// SDL_Surface *load_image( std::string filename, int alpha )
SDL_Surface *load_image( const char * filename, int alpha )
{
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *optimized_image = NULL;
	
	loaded_image = IMG_Load ( filename); //.c_str() );
	if( loaded_image != NULL )
	{
		if(alpha)
			optimized_image = SDL_DisplayFormatAlpha( loaded_image );
		else
			optimized_image = SDL_DisplayFormat( loaded_image );
		SDL_FreeSurface ( loaded_image );
	}
	else
	{
		printf("Nao carrego");
		closeWindow();
	}
	return optimized_image;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );
}

int fps(int * start)
{
	int end = SDL_GetTicks();
	if( (1000/30) > ( end - *start ) )
		return 0;
	
	*start = SDL_GetTicks();
	return 1;
}

int timer(int * start, int time)
{
	int end = SDL_GetTicks();
	if( time > ( end - *start ) )
		return 0;
	*start = SDL_GetTicks();
	return 1;
}
