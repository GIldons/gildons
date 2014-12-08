#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "headers/basic.h"
#include "headers/game_logic.h"
#include "headers/screen_opt.h"
#include <string.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGTH = 600;
const int SCREEN_BPP = 32;

int DISPLAY_WIDTH = 800;
int DISPLAY_HEIGTH = 600;

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *display = NULL;

int init()
{

	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return 0;
	const SDL_VideoInfo *info = SDL_GetVideoInfo();
	int surface_flags;
	surface_flags = SDL_SWSURFACE;
	if(info->current_w < SCREEN_WIDTH || info->current_h < SCREEN_HEIGTH)
	{
		DISPLAY_WIDTH = info->current_w;
		DISPLAY_HEIGTH = info->current_h;
		surface_flags |= SDL_FULLSCREEN;
	}
	char en_var[] = "SDL_VIDEO_CENTERED=center";
	SDL_putenv(en_var);
	display = SDL_SetVideoMode(DISPLAY_WIDTH, DISPLAY_HEIGTH, SCREEN_BPP, surface_flags);
	if( display == NULL )
		return 0;
	screen = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGTH, SCREEN_BPP, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	if( screen == NULL )
		return 0;
	if( TTF_Init() == -1 )
		return 0;
	SDL_WM_SetCaption("FireFlight - ECE 453 Project", NULL );
	return 1;
}

int load_files()
{
	background = load_image ( "files/fundo.png", 0 );
	if( background == NULL )
		return 0;
	return 1;
}

void clean_up()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(screen);
	SDL_Quit();
}

SDL_Surface *make_screen()
{
	if( init() == 0 )
		return NULL;
	if( load_files()  == 0 )
		return NULL;
	return screen;
}

void screen_clean()
{
	apply_surface( 0, 0, background, screen, NULL );
}

void closeWindow()
{
	clean_up();
}

int update_display(Sint16 x, Sint16 y)
{
	SDL_Rect teste = {x, y, (Uint16)DISPLAY_WIDTH, (Uint16)DISPLAY_HEIGTH};
	apply_surface(0,0, screen, display, &teste);
	if(SDL_Flip(display) == -1)
			return 0;
	return 1;
}

int apply_screen(SDL_Surface ** Surfaces, Spot table[][8], int ** dados, TTF_Font ** font)
{
		apply_surface(0, 0, Surfaces[1], Surfaces[0], NULL);
		show_table(table, Surfaces[2], Surfaces[3], Surfaces[6], Surfaces[0]);
		screen_text(Surfaces, dados, font);
		return(update_display(0,0));
}
