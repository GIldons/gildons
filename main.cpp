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

SDL_Event event;

int main()
{
	int exit = 1, fire_count = 0, fire_ext = 0, start = 0, water = 100, lvl = 0, temp;
	int reset = 0, difc_lvl[100];
	Spot table[10][10];
	SDL_Surface * screen = make_screen();
	SDL_Surface * back = NULL;
	SDL_Surface * tree = NULL;
	SDL_Surface * tree_fire = NULL;
	SDL_Surface * rect = NULL;
	
	int * dados[] = {&fire_count, &fire_ext, &water, &lvl, &start, &reset};
	int fd;
	
	TTF_Font *font_small = NULL, *font_big = NULL;
	font_small = TTF_OpenFont("files/LiberationSans-BoldItalic.ttf",35);
	font_big = TTF_OpenFont("files/LiberationSans-BoldItalic.ttf",50);
	if(font_small == NULL)
	{
		printf("Nao Carrego a fonte\n");
	}
	TTF_Font * font[] = {font_small, font_big};
	
	back = load_image("files/fundo.png");
	tree = load_image("files/trees_2.png",1);
	tree_fire = load_image("files/trees_fire_2.png",1);
	rect = load_image("files/rect.png",1);
	
	SDL_Surface * Surfaces[] = {screen, back, tree, tree_fire, rect};
	
	init_table(table, fire_count);
	difc_table(difc_lvl, 50 + 25 * lvl);
	fd = init_serial();
	
	turn_onoff(1);

	send_output(fd, "+\n");
	send_output(fd, "SF,1\n");
	send_output(fd, "SS,C0000000\n");
	send_output(fd, "SR,92000000\n");
	send_output(fd, "R,1\n");
	
	while(event.type != SDL_QUIT && exit)
	{
		temp = lvl;
		while(SDL_PollEvent(&event))
		{
			mouse_events(event, dados);
			if(temp != lvl)
			{
				difc_table(difc_lvl, 50 + 25 * lvl);
				temp = lvl;
			}
		}
		if(!apply_screen(Surfaces, table, dados, font))
		{
			printf("Error updating screen");
			exit = 0;
		}
		
		if(difc_lvl[rand() % 100] && start)
		{
			if(reset)
			{
				fire_count = fire_ext = 0;
				water = 100;
				init_table(table,fire_count);
				reset = 0;
				start = 0;
			}
			else
			{
//				get_input(fd, hue,6);
				fire_spread(table, fire_count);
//				send_output(fd, ha,4);
			}
			
		}
		SDL_Delay(1000);
	}
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
