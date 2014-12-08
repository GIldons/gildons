#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "headers/basic.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "headers/basic.h"
#include "headers/screen.h"
#include "headers/game_logic.h"
#include "headers/screen_opt.h"
#include "headers/I_O.h"
#include "headers/neolib.h"

SDL_Event event;

#define GAMETIME 1000

int main()
{
	int exit = 1, fire_count = 0, fire_ext = 0, start = 0, water = 100, lvl = 0, temp;
	int screen_time = 0, spreed_time = 0, win = -1;
	int reset = 0, difc_lvl[100];
	int fd = -1;
	Spot table[8][8];
	SDL_Surface * screen = make_screen();
	SDL_Surface * tree_fire = NULL;
	TTF_Font * font_small = NULL;
	SDL_Surface * plexus = NULL;
	TTF_Font * font_big = NULL;
	SDL_Surface * back = NULL;
	SDL_Surface * tree = NULL;
	SDL_Surface * rect = NULL;
	SDL_Surface * base = NULL;
	
	SDL_Surface * Surfaces[] = {screen, back, tree, tree_fire, rect, plexus, base};
	int * dados[] = {&fire_count, &fire_ext, &water, &lvl, &start, &reset, &win};
	TTF_Font * font[] = {font_small, font_big};
	
	if(load(Surfaces, font))
		exit = 0;
	if(init_serial(&fd) == 1)
		exit = 0;
	
	difc_table(difc_lvl, 50 + 25 * lvl);
	init_table(table, dados);
	
	turn_onoff(0);
	SDL_Delay(10);
// 	openBluetooh(fd);
	turn_onoff(1);
// 	fd = connectBluART();
	screen_time = spreed_time = SDL_GetTicks();
	
	clearAll(1, 1, 1);
	while(event.type != SDL_QUIT && exit)
	{
		temp = lvl;
		//Check for any User input over SDL interface
		while(SDL_PollEvent(&event))
		{
			mouse_events(&event, dados, table, 1);
			if(temp != lvl)
			{
				difc_table(difc_lvl, 50 + 25 * lvl);
				temp = lvl;
			}
		}
		
		//Update the screen at 30 FPS
		if(fps(&screen_time))
		{
// 			clearAll(1, 0, 0);
// 			int i;
// 			for(i = 0; i < 1000 ; i++)
// 			{
// 				writeTile(i,0x0000FF);
// 				printf("i = %d\n", i);
// 				SDL_Delay(1000);
// 			}
			if(!apply_screen(Surfaces, table, dados, font))
			{
				printf("Error updating screen\n");
				exit = 0;
			}
		}
		
		//Update the game at GAMETIME sec. based on current status
		if(timer(&spreed_time, GAMETIME))
		{
			if(difc_lvl[rand() % 100] && start)
			{
				if(reset)
					init_table(table, dados);
				else
					fire_spread(table, dados);
			}
		}
		read_heli(table, fd, dados);
		SDL_Delay(.1);
	}
	
	//Close and free all surfaces and fds
	SDL_FreeSurface(back);
	SDL_FreeSurface(tree);
	SDL_FreeSurface(tree_fire);
	TTF_CloseFont(font_small);
	TTF_CloseFont(font_big);
	SDL_Quit();
	turn_onoff(0);
	close(fd);
	return 0;
}
