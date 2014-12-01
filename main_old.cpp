#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "headers/basic.h"
#include "headers/screen.h"
#include "headers/field.h"
#include "headers/solver.h"
#include "headers/mfun.h"
#include "headers/answerBack.h"
#include "headers/initial.h"
#include "headers/signal.h"

SDL_Event event;

int main()
{
	SDL_Surface *screen = make_screen();
	screen_clean();
	FPS_Control main;
	Field A(000, 127, 85, 20, 4, screen);
	Field B(18, 127, 85, 20, 3, screen);
	Field C(179, 127, 85, 20, 2, screen);
	Field D(341, 127, 85, 20, 1, screen);
	Field E(502, 127, 85, 20, 0, screen);
// 	Field F(025, 150, 85, 20, 9, screen);
// 	Field G(165, 150, 85, 20, 8, screen);
// 	Field H(310, 150, 85, 20, 7, screen);
// 	Field I(455, 150, 85, 20, 6, screen);
	Field J(662, 127, 85, 20, 5, screen);
	Initial i_A(035, 223, 85, 20, 0, screen);
	Initial i_B(330, 223, 85, 20, 1, screen);
	Initial i_C(630, 223, 85, 20, 2, screen);
	Initial i_D(455, 223, 85, 20, 3, screen);
	Signal degrau(34, 323, 155, 25, 0, screen);
	Signal uexp(233, 323, 155, 25, 1, screen);
	Signal ucos(433, 323, 155, 25, 2, screen);
	Signal usin(633, 323, 155, 25, 3, screen);
	Field * arrField[] = {&A, &B, &C, &D, &E, &J};//, &G, &H, &I, &J};
	Signal * arrSignal[] = {&degrau, &uexp, &ucos, &usin};
	Initial * arrInitial[] = {&i_A, &i_B, &i_C, &i_D};
	showall(arrField, arrSignal, arrInitial);

	float a[]={0.,0.,0.,0.,0.,0.,0.};
	float i_a[]={0.,0.,0.,0.};
	Sint16 x = 0, y = 0;
	Sint16 MAX_x, MAX_y;
	const SDL_VideoInfo *info = SDL_GetVideoInfo();
	if(info->current_w < 822 || info->current_h < 672)
	{
		MAX_x = 822-info->current_w; //Caso a SCREEN (screen.h) sofrer alteração mudar para valor
		MAX_y = 672-info->current_h;//correpondente. O numero 10 é fator de correção para visualizar a tela
	}
	else
		MAX_x = MAX_y = 0;
    int quit = 0;
	while(event.type != SDL_QUIT && !quit)
	{
		main.Start();
		display_movement(x, y, MAX_x, MAX_y);
		while(SDL_PollEvent(&event))
		{
			screen_clean();
			showall(arrField, arrSignal, arrInitial);
			handle_mouse_events(arrField, arrSignal, arrInitial, x, y, quit);
			get_value(arrField, arrSignal, arrInitial, a, i_a);
			naturalAnswer(solver(a), a, i_a);
		}
		if(!update_display(x, y))
			return 0;

		main.End();
	}
	closeWindow();
	return 1;
}
