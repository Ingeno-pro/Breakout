#ifndef __GUI_H__
#define __GUI_H__
#include <stdio.h>
#include <caca.h>
#include "const.h"
void drawGUI(caca_canvas_t *cv, char str[6], int score, int ballx, int bally, char ball);

void winGUI(caca_canvas_t *cv);
void looseGUI(caca_canvas_t *cv);

#endif
