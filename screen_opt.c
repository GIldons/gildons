#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "headers/basic.h"
#include "headers/game_logic.h"
#include "headers/I_O.h"

SDL_Color textColor = {0x00, 0x00, 0x00, 0x00};

void screen_text(SDL_Surface ** Surfaces, int ** dados, TTF_Font ** font)
{
	SDL_Surface * stemp = NULL;
	char * temp;
	temp = (char *) malloc(150 * sizeof(char));
	
	int off_x = 0;
	if(*dados[3] == 2)
		off_x = 333;
	else if(*dados[3] == 1)
		off_x = 283;
	else
		off_x = 233;
	apply_surface(off_x, 256, Surfaces[4], Surfaces[0], NULL);

	sprintf(temp, "Difficulty lvl:   1   2   3");
	stemp = TTF_RenderUTF8_Blended(font[0], temp, textColor);
	apply_surface(10, 255, stemp, Surfaces[0], NULL);
	SDL_FreeSurface(stemp);
	
	
	sprintf(temp, "Remaining Fires: %d", *(dados[0]));
	stemp = TTF_RenderUTF8_Blended(font[0], temp, textColor);
	apply_surface(10, 305, stemp, Surfaces[0], NULL);
	SDL_FreeSurface(stemp);
	
	sprintf(temp, "Fires Extinguished: %d", *(dados[1]));
	stemp = TTF_RenderUTF8_Blended(font[0], temp, textColor);
	apply_surface(10, 355, stemp, Surfaces[0], NULL);
	SDL_FreeSurface(stemp);
	
	sprintf(temp, "Water Level: %d", *(dados[2]));
	stemp = TTF_RenderUTF8_Blended(font[0], temp, textColor);
	apply_surface(10, 405, stemp, Surfaces[0], NULL);
	SDL_FreeSurface(stemp);
	
	
	if(*dados[4])
	{
		if(*dados[6] == -1)
			sprintf(temp, "PAUSE");
		else if(*dados[6] == 1)
			sprintf(temp, "YOU WIN!");
		else if(*dados[6] == 0)
			sprintf(temp, "Game Over!");
		stemp = TTF_RenderUTF8_Blended(font[1], temp, textColor);
		apply_surface(100, 455, stemp, Surfaces[0], NULL);
		SDL_FreeSurface(stemp);
		
		sprintf(temp, "RESET");
		stemp = TTF_RenderUTF8_Blended(font[1], temp, textColor);
		apply_surface(100, 525, stemp, Surfaces[0], NULL);
		SDL_FreeSurface(stemp);
	}
	else
	{
		sprintf(temp, "START");
		stemp = TTF_RenderUTF8_Blended(font[1], temp, textColor);
		apply_surface(100, 455, stemp, Surfaces[0], NULL);
		SDL_FreeSurface(stemp);
	}
	free(temp);
	
	apply_surface(600, 100, Surfaces[5], Surfaces[0], NULL);
}

//Temporary function until SDL Screen is not implemented - FINAL
void show_table(Spot table[][8], SDL_Surface * tree, SDL_Surface * tree_fire, SDL_Surface * base, SDL_Surface * screen)
{
	int i, j;
	int off_x = 395, off_y = 180;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
		{
			if(table[i][j].fire_lvl == 0)
				apply_surface( off_x + i*45, off_y + j*50, tree, screen, NULL);
			else if(table[i][j].fire_lvl == 1)
				apply_surface( off_x + i*45, off_y + j*50, tree_fire, screen, NULL);
			else if(table[i][j].fire_lvl == -2)
				apply_surface( off_x + i*45, off_y + j*50, base, screen, NULL);
// 			send_tile(table, i, j);
		}
}

void mouse_events(SDL_Event * event, int ** dados, Spot table[][8], int teste_mode)
{
	int x, y;
	if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		if(event->button.button == SDL_BUTTON_LEFT)
		{
			x = event->motion.x;
			y = event->motion.y;
			if(( x > 233) && ( x < (233 + 39) ) && ( y > 256) && ( y < (256 + 39)))
				*(dados[3]) = 0;
			if(( x > 283) && ( x < (285 + 39) ) && ( y > 256) && ( y < (256 + 39)))
				*(dados[3]) = 1;
			if(( x > 333) && ( x < (335 + 39) ) && ( y > 256) && ( y < (256 + 39)))
				*(dados[3]) = 2;
			if(( x > 100) && ( x < (100 + 165) ) && ( y > 455) && ( y < (455 + 50)))
				*(dados[4]) = !*(dados[4]);
			if(( x > 100) && ( x < (100 + 165) ) && ( y > 525) && ( y < (525 + 50)))
				*(dados[5]) = 1;
			
			//Use user input over the title to change status
			if(teste_mode)
			{
				int i, j;
				int off_x = 395, off_y = 180;
				if((x > off_x) && (x < off_x + 45*8) && (y > off_y) && (y < off_y + 50*8))
				{
					i = (x - off_x)/45;
					j = (y - off_y)/50;
					if(table[i][j].fire_lvl == 0)
					{
						table[i][j].fire_lvl = 1;
						if( (*dados[0]) >= 0 )
							(*dados[0])=(*dados[0]) + 1;
					}
					else if(table[i][j].fire_lvl == 1)
					{
						table[i][j].fire_lvl = 0;
						if( *(dados[0]) <= 36 )
							*(dados[0])=(*dados[0]) - 1;
					}
				}
			}
		}
	}
}