/*Game Logic*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "headers/basic.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "headers/basic.h"
#include "headers/screen.h"

#define NW 1
#define N 2
#define NE 3
#define E 4
#define SE 5
#define S 6
#define SW 7
#define W 8

//Set real spots with 0, for no fire, and auxliary spots with -1
void init_table(Spot table[][8], int &fire_count)
{
	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
		{
			if(i == 0 || i == 7)
				table[i][j].fire_lvl = -1;
			else if(j == 0 || j == 7)
				table[i][j].fire_lvl = -1;
			else
				table[i][j].fire_lvl = 0;
		}
	srand(time(NULL));
	table[(rand() % 6 + 1)][(rand() % 6 + 1)].fire_lvl = 1;
	fire_count++;
}

//Until this point, the next fire spot is calculated here, but the idea is change this to an random
//table for different difficulties levels. For example, 3 charts with 100 positions and some of this positions
//are filled and some not. The number of filled positions incrase with the difficult level.
void fire_spread(Spot table[][8], int &fire_count)
{
	int i, j, next_fire, exit;
	exit = 0;
	if(fire_count < 36)
	{
		for(i = 0; i < 8 && !exit; i++)
			for(j = 0; j < 8 && !exit; j++)
			{
				if(table[i][j].fire_lvl > 0)
				{
					/*Determines a new fire spot around the current spot. Start at up left corn: 1 2 3 4 5 6 7 8*/
					next_fire = rand() % 6 + 1;
					switch(next_fire)
					{
						case NW:
							if(table[i-1][j-1].fire_lvl > -1 && table[i-1][j-1].fire_lvl < 1)
							{
								table[i-1][j-1].fire_lvl++;
								exit = 1;
								fire_count++;
							}
							break;
						case N:
							if(table[i-1][j].fire_lvl > -1 && table[i-1][j].fire_lvl < 1)
							{
								table[i-1][j].fire_lvl++;
								exit = 1;
								fire_count++;
							}
								break;
						case NE:
							if(table[i-1][j+1].fire_lvl > -1 && table[i-1][j+1].fire_lvl < 1)
							{
								table[i-1][j+1].fire_lvl++;
								exit = 1;
								fire_count++;
							}
								break;
						case E:
							if(table[i][j+1].fire_lvl > -1 && table[i][j+1].fire_lvl < 1)
							{
								table[i][j+1].fire_lvl++;
								exit = 1;
								fire_count++;
							}
								break;
						case SE:
							if(table[i+1][j+1].fire_lvl > -1 && table[i+1][j+1].fire_lvl < 1)
							{
								table[i+1][j+1].fire_lvl++;
								exit = 1;
								fire_count++;
							}
								break;
						case S:
							if(table[i+1][j].fire_lvl > -1 && table[i+1][j].fire_lvl < 1)
							{
								table[i+1][j].fire_lvl++;
								exit = 1;
								fire_count++;
							}
								break;
						case SW:
							if(table[i+1][j-1].fire_lvl > -1 && table[i+1][j-1].fire_lvl < 1)
							{
								table[i+1][j-1].fire_lvl++;
								exit = 1;
								fire_count++;
							}
								break;
						case W:
							if(table[i][j-1].fire_lvl > -1 && table[i][j-1].fire_lvl < 1)
							{
								table[i][j-1].fire_lvl++;
								exit = 1;
								fire_count++;
							}
								break;
						default:
							break;
					}
				}
			}
	}
}

void difc_table(int * lvl_table, int lvl)
{
	srand(time(NULL));
	int i = 0, b = 0;
	for(int i = 0; i < 100; i++)
		lvl_table[i] = 0;
	for(i = 0; i < lvl; i++)
	{
		b = rand() % 100;
		while(lvl_table[b] != 0)
			b = rand() % 100;
		lvl_table[b] = 1;
	}
}