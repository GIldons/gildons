#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <sstream>
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

// FPS_Control::FPS_Control(int fps)
// {
// 	FPS = fps;
// }
// 
// void FPS_Control::Start()
// {
// 	start = SDL_GetTicks();
// }
// 
// void FPS_Control::End()
// {
// 	end = SDL_GetTicks();
// 	if( (1000/FPS) > ( end - start ) )
// 		SDL_Delay( (1000/FPS ) - ( end - start ) );
// }

// const char* ftoa( float ftoa_f )
// { 
// 	std::stringstream ftoa_ss;
// 	ftoa_ss << ftoa_f;
// 	std::string ftoa_c;
// 	ftoa_c = ftoa_ss.str();
// 	return ftoa_c.c_str();
// }
