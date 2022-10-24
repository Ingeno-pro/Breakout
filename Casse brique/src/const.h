#ifndef __CONST_H__
#define __CONST_H__

#define MAP_W 8
#define MAP_H 4
#define DEFAULT_BALL_X 37
#define DEFAULT_BALL_Y 16
#define BALL_W 4
#define BALL_H 2
#define BRICK_W 10
#define BRICK_H 2
#define PLAYER_Y 29
#define PLAYER_W 10
#define PLAYER_H 2
#define FPS 33

#define LEVEL_EXT ".lvl"

typedef enum BALL_DIRECTION{

	DOWN,
	UP,
	RIGHT_UP,
	LEFT_UP,
	RIGHT_DOWN,
	LEFT_DOWN

}BALL_DIRECTION;

typedef enum BRICK{

	AIR,
	WEAK,
	NORMAL,
	HARD,
	VERY_HARD,
	ASIAN,

}BRICK;


#endif
