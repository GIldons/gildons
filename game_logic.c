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
//Use j for line and i for collum
void init_table(Spot table[][8], int ** dados)
{
	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
		{
			if(i == 0 || i == 7)
				table[i][j].fire_lvl = -1;
			else if(j == 0 || j == 7)
				table[i][j].fire_lvl = -1;
			else if(j == 8 && i == 4)
				table[i][j].fire_lvl = -2;
			else
				table[i][j].fire_lvl = 0;
		}
	table[1][1].ID = 0xCB;
	table[2][1].ID = 0xCD;
	table[3][1].ID = 0xCF;
	table[4][1].ID = 0xD1;
	table[5][1].ID = 0xD3;
	table[6][1].ID = 0xD5;
	table[1][2].ID = 0xBB;
	table[2][2].ID = 0xBD;
	table[3][2].ID = 0xBF;
	table[4][2].ID = 0xC5;
	table[5][2].ID = 0xC7;
	table[6][2].ID = 0xC9;
	table[1][3].ID = 0xAF;
	table[2][3].ID = 0xB1;
	table[3][3].ID = 0xB3;
	table[4][3].ID = 0xB5;
	table[5][3].ID = 0xB7;
	table[6][3].ID = 0xB9;
	table[1][4].ID = 0xA3;
	table[2][4].ID = 0xA5;
	table[3][4].ID = 0xA7;
	table[4][4].ID = 0xA9;
	table[5][4].ID = 0xAB;
	table[6][4].ID = 0xAD;
	table[1][5].ID = 0x95;
	table[2][5].ID = 0x97;
	table[3][5].ID = 0x99;
	table[4][5].ID = 0x9B;
	table[5][5].ID = 0x9D;
	table[6][5].ID = 0x9F;
	table[1][6].ID = 0x89;
	table[2][6].ID = 0x88;
	table[3][6].ID = 0x8D;
	table[4][6].ID = 0x8F;
	table[5][6].ID = 0x91;
	table[6][6].ID = 0x93;
	
	for(i = 0; i < 6; i++)
		for(j = 0; j < 6; j++)
			table[i+1][j+1].LED_ID = (j + 6*i);
		
	srand(time(NULL));
	i = (rand() % 6 + 1);
	j = (rand() % 6 + 1);
	int k;
	for(k = 0; k < 4; k++)
		while(i != 4 && j != 8)
		{
			i = (rand() % 6 + 1);
			j = (rand() % 6 + 1);
			table[i][j].fire_lvl = 1;
			*(dados[0]) = *(dados[0]) + 1;
		}
	table[4][6].fire_lvl = -2;
	
	*(dados[1]) = 0;
	*(dados[2]) = 100;
	*(dados[4]) = 0;
	*(dados[5]) = 0;
	*(dados[6]) = -1;
}

//Until this point, the next fire spot is calculated here, but the idea is change this to an random
//table for different difficulties levels. For example, 3 charts with 100 positions and some of this positions
//are filled and some not. The number of filled positions incrase with the difficult level.
void fire_spread(Spot table[][8], int  ** dados)
{
	int i, j, next_fire, exit;
	exit = 0;
	if(*(dados[0]) == 35)
		*(dados[6]) = 0;
	if(*(dados[0]) - *(dados[1]) == 0 || *(dados[0]) == 0)
	{
		*(dados[6]) = 1;
		exit = 0;
	}
	
	if(*(dados[0]) < 35)
	{
		for(i = 1; i < 7 && !exit; i++)
			for(j = 1; j < 7 && !exit; j++)
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
								*(dados[0]) = *(dados[0]) + 1;
							}
							break;
						case N:
							if(table[i-1][j].fire_lvl > -1 && table[i-1][j].fire_lvl < 1)
							{
								table[i-1][j].fire_lvl++;
								exit = 1;
								*(dados[0]) = *(dados[0]) + 1;
							}
								break;
						case NE:
							if(table[i-1][j+1].fire_lvl > -1 && table[i-1][j+1].fire_lvl < 1)
							{
								table[i-1][j+1].fire_lvl++;
								exit = 1;
								*(dados[0]) = *(dados[0]) + 1;
							}
								break;
						case E:
							if(table[i][j+1].fire_lvl > -1 && table[i][j+1].fire_lvl < 1)
							{
								table[i][j+1].fire_lvl++;
								exit = 1;
								*(dados[0]) = *(dados[0]) + 1;
							}
								break;
						case SE:
							if(table[i+1][j+1].fire_lvl > -1 && table[i+1][j+1].fire_lvl < 1)
							{
								table[i+1][j+1].fire_lvl++;
								exit = 1;
								*(dados[0]) = *(dados[0]) + 1;
							}
								break;
						case S:
							if(table[i+1][j].fire_lvl > -1 && table[i+1][j].fire_lvl < 1)
							{
								table[i+1][j].fire_lvl++;
								exit = 1;
								*(dados[0]) = *(dados[0]) + 1;
							}
								break;
						case SW:
							if(table[i+1][j-1].fire_lvl > -1 && table[i+1][j-1].fire_lvl < 1)
							{
								table[i+1][j-1].fire_lvl++;
								exit = 1;
								*(dados[0]) = *(dados[0]) + 1;
							}
								break;
						case W:
							if(table[i][j-1].fire_lvl > -1 && table[i][j-1].fire_lvl < 1)
							{
								table[i][j-1].fire_lvl++;
								exit = 1;
								*(dados[0]) = *(dados[0]) + 1;
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
	for( i = 0; i < 100; i++)
		lvl_table[i] = 0;
	for(i = 0; i < lvl; i++)
	{
		b = rand() % 100;
		while(lvl_table[b] != 0)
			b = rand() % 100;
		lvl_table[b] = 1;
	}
}