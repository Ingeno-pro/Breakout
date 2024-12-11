#include "const.h"
#ifndef __EVENT_H__
#define __EVENT_H__

int ballColWithPlayer(int ballx, int bally, int playerx);
int ballColWithPlayerZoom(int ballx, int bally, int playerx);
int ballColWithBorder(int ballx, int bally);
int ballColWithGround(int bally);
int ballColWithTop(int bally);
int ballColWithBrick(int ballx, int bally, int map[MAP_W][MAP_H]);
int doesPlayerWin(int map[MAP_W][MAP_H]);


#endif
