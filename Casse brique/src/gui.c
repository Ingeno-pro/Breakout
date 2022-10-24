#include "gui.h"

void drawGUI(caca_canvas_t *cv, char str[6], int score, int ballx, int bally, char ball){
	
	caca_set_color_ansi(cv, CACA_BLACK, CACA_WHITE);
	caca_printf(cv, 0, 0, "Score:%d", score);
	caca_put_str(cv, 0, 31, "Action:");
	caca_printf(cv, 7, 31, "%s", str);
	caca_put_str(cv, 16, 31, "Ball coordinate:");
	caca_printf(cv, 32, 31, "%d, %d", ballx, bally);
	caca_put_str(cv, 48, 31, "Life:");
	caca_printf(cv, 53, 31, "%d", ball);
	

}
void winGUI(caca_canvas_t *cv){

	caca_set_color_ansi(cv, CACA_BLACK, CACA_WHITE);
	caca_printf(cv, 35, 16, "You Win !");

}
void looseGUI(caca_canvas_t *cv){

	caca_set_color_ansi(cv, CACA_BLACK, CACA_WHITE);
	caca_printf(cv, 35, 16, "You Loose !");

}

