#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <caca.h>
#include "gui.h"
#include "event.h"
#include "level_manager.h"
#include "const.h"

unsigned long long getTimeInMilliseconds();
void ballMove(int *ballx, int *bally, int direction);
void drawBrickZone(caca_canvas_t *cv, int map[MAP_W][MAP_H]);
void newBall(int *ballx, int *bally, int *direction);

int loadLevel(int map[MAP_W][MAP_H], char levelname[8]);

int main(void){

	
	caca_canvas_t *cv;
	caca_display_t *dp;
	caca_event_t ev;
	dp = caca_create_display(NULL);
	caca_set_display_time(dp, FPS);
	if(!dp) return 1;
	
	int score = 0;
	int playerx=34;
	char ball=3;
	int ballx, bally, ball_direction;
	newBall(&ballx, &bally, &ball_direction);
	int map[MAP_W][MAP_H]= {
	{0, 0, 0, 0}, 
	{0, 0, 0, 0}, 
	{0, 0, 0, 0}, 
	{0, 0, 0, 0}, 
	{0, 0, 0, 0}, 
	{0, 0, 0, 0}, 
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	};
	loadLevel(map, "cc");
	
	char action[6] = "None\0";
	cv = caca_get_canvas(dp);
	caca_set_display_title(dp, "Breakout");
	caca_set_color_ansi(cv, CACA_WHITE, CACA_WHITE);
	drawGUI(cv, action, score, ballx, bally, ball);
	caca_draw_box(cv, playerx, PLAYER_Y, PLAYER_W, PLAYER_H, 'c');
	caca_draw_box(cv, ballx, bally, BALL_W, BALL_H, '.');
	drawBrickZone(cv, map);
	caca_refresh_display(dp);
	unsigned long long tms = getTimeInMilliseconds();   //Program running schreduler
	unsigned long long tlams = getTimeInMilliseconds(); //Last action schreduler
	unsigned long long tlpcms = getTimeInMilliseconds();//Last player touch schreduler
	unsigned long long tlbcms = getTimeInMilliseconds();//Last brick touch schreduler
	unsigned long t = (unsigned long)time(NULL);
	//main loop
	int loop = 1;
	while(loop){
		caca_get_event(dp, CACA_EVENT_KEY_PRESS, &ev, 1);
		if(caca_get_event_type(&ev) == CACA_EVENT_KEY_PRESS){
			switch(caca_get_event_key_ch(&ev)){
				case CACA_KEY_RIGHT:
					(playerx + PLAYER_W > caca_get_canvas_width(cv)-1) ?  0 : playerx++;
					strcpy(action, "RIGHT\0");
					tlams = getTimeInMilliseconds();
				break;
				case CACA_KEY_LEFT:
					(playerx <= 0) ? 0 : playerx--;
					strcpy(action, "LEFT\0");
					tlams = getTimeInMilliseconds();
				break;
				case CACA_KEY_ESCAPE:
					loop = 0;
				break;
				default:
				//strcpy(action, "None\0");
				break;
			}
				
		}else if(tlams + FPS*10 <= getTimeInMilliseconds()){
				strcpy(action, "None\0");
		}
		if(tms + FPS*3 <= getTimeInMilliseconds()){
			ballMove(&ballx, &bally, ball_direction);
			tms = getTimeInMilliseconds();
		}
		if(doesPlayerWin(map)){winGUI(cv); caca_refresh_display(dp); sleep(5); loop = 0; break;}
		if(ballColWithPlayer(ballx, bally, playerx)){
			//ball_direction = ballColWithPlayerZoom(ballx, bally, playerx, playery);
			switch(action[0]){
				case 'N':
					ball_direction = UP;
				break;
				case 'R':
					ball_direction = RIGHT_UP;
				break;
				case 'L':
					ball_direction = LEFT_UP;
				break;
			}
			if(tlpcms + FPS*10 <= getTimeInMilliseconds()){
				score++;
				tlpcms = getTimeInMilliseconds();
			}
		}else if(tlbcms + FPS*10 <= getTimeInMilliseconds() && ballColWithBrick(ballx, bally, map)){
			if(ball_direction == UP){ball_direction = DOWN;
			}else if(ball_direction == RIGHT_UP){ball_direction = RIGHT_DOWN;
			}else if(ball_direction == LEFT_UP){ball_direction = LEFT_DOWN;}
			tlbcms = getTimeInMilliseconds();
			score+=10;
		}else if(ballColWithBorder(ballx, bally) == UP){
			 if(ball_direction == LEFT_UP){ball_direction = RIGHT_UP;
			}else if(ball_direction == LEFT_DOWN){ball_direction = RIGHT_DOWN;}
		}else if(ballColWithBorder(ballx, bally) == RIGHT_UP){
			 if(ball_direction == RIGHT_UP){ball_direction = LEFT_UP;
			}else if(ball_direction == RIGHT_DOWN){ball_direction = LEFT_DOWN;}
		}else if(ballColWithGround(bally)){
			if(ball==1){
				looseGUI(cv); caca_refresh_display(dp); sleep(5); loop = 0; break;
			}else{
				ball--;
				newBall(&ballx, &bally, &ball_direction);
			}
		}else if(ballColWithTop(bally)){
		/*	if(ball==1){
				loop=0;
			}else{
				ball--;
				newBall(&ballx, &bally, &ball_direction);
			}*/
			ball_direction = DOWN;
		}
		
		//Clear
		caca_set_color_ansi(cv, CACA_BLACK, CACA_BLACK);
		caca_clear_canvas(cv);
		//DrawGUI
		drawGUI(cv, action, score, ballx, bally, ball);
		//Change color
		caca_set_color_ansi(cv, CACA_WHITE, CACA_WHITE);
		//draw player
		caca_draw_box(cv, playerx, PLAYER_Y, PLAYER_W, PLAYER_H, 'c');
		//draw ball
		caca_draw_box(cv, ballx, bally, BALL_W, BALL_H, '.');
		//draw bricks
		drawBrickZone(cv, map);
		
		caca_refresh_display(dp);
		usleep(5000);
	}
	caca_free_display(dp);
	return 0;
}
void newBall(int *ballx, int *bally, int *direction){

	*ballx = DEFAULT_BALL_X;
	*bally = DEFAULT_BALL_Y;
	*direction = DOWN;

}
void drawBrickZone(caca_canvas_t *cv, int map[MAP_W][MAP_H]){
	for(int i = 0; i < MAP_W;i++){
		for(int j = 0;j < MAP_H;j++){
			switch(map[i][j]){
				case 1:
					caca_set_color_ansi(cv, CACA_WHITE, CACA_WHITE);
					caca_draw_box(cv, i*BRICK_W, j*BRICK_H+1, BRICK_W, BRICK_H, 'b');
				break;
				case 2:
					caca_set_color_ansi(cv, CACA_YELLOW, CACA_YELLOW);
					caca_draw_box(cv, i*BRICK_W, j*BRICK_H+1, BRICK_W, BRICK_H, 'b');
				break;
				case 3:
					caca_set_color_ansi(cv, CACA_CYAN, CACA_CYAN);
					caca_draw_box(cv, i*BRICK_W, j*BRICK_H+1, BRICK_W, BRICK_H, 'b');
				break;
				case 4:
					caca_set_color_ansi(cv, CACA_GREEN, CACA_GREEN);
					caca_draw_box(cv, i*BRICK_W, j*BRICK_H+1, BRICK_W, BRICK_H, 'b');
				break;
				case 5:
					caca_set_color_ansi(cv, CACA_RED, CACA_RED);
					caca_draw_box(cv, i*BRICK_W, j*BRICK_H+1, BRICK_W, BRICK_H, 'b');
				break;
				
			}
		}
	}
	caca_set_color_ansi(cv, CACA_BLACK, CACA_WHITE);
}
void ballMove(int *ballx, int *bally, int direction){

	switch(direction){
		case DOWN:
			*bally = *bally + 1;
		break;
		case UP:
			*bally = *bally - 1;
		break;
		case RIGHT_UP:
			*ballx = *ballx + 1;
			*bally = *bally - 1;
		break;
		case LEFT_UP:
			*ballx = *ballx - 1;
			*bally = *bally - 1;
		break;
		case RIGHT_DOWN:
			*ballx = *ballx + 1;
			*bally = *bally + 1;
		break;
		case LEFT_DOWN:
			*ballx = *ballx - 1;
			*bally = *bally + 1;
		break;
		default:
			exit(0);
		break; 
		
	}

}
unsigned long long getTimeInMilliseconds(){

	struct timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long long tms = (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;

	return tms;
}

