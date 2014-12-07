#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string.h>
#include "headers/basic.h"
#include "headers/screen.h"
#include "SDL/SDL_ttf.h"

int load(SDL_Surface ** Surfaces, TTF_Font ** font)
{
	
	// {font_small, font_big};
	font[0] = TTF_OpenFont("files/LiberationSans-BoldItalic.ttf",35);
	font[1] = TTF_OpenFont("files/LiberationSans-BoldItalic.ttf",50);
	if(font[0] == NULL)
	{
		printf("Erro Loading fonts\n");
		return 1;
	}
	
	//{screen, back, tree, tree_fire, rect, plexus, base};
	Surfaces[1] = load_image("files/fundo.png", 0);
	Surfaces[2] = load_image("files/trees_2.png",1);
	Surfaces[3] = load_image("files/trees_fire_2.png",1);
	Surfaces[4] = load_image("files/rect.png",1);
	Surfaces[5] = load_image("files/plexus2.png",1);
	Surfaces[6] = load_image("files/base.png",1);
	
	int i = 0;
	for(i = 0; i < 7; i++)
		if(Surfaces[i] == NULL)
		{
			printf("Error loading image %d\n", i);
			return 1;
		}
	return 0;;
}

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
