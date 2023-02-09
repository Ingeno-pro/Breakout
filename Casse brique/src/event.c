#include "event.h"

int ballColWithPlayer(int ballx, int bally, int playerx){
	if(ballx + BALL_W >= playerx && ballx < playerx + PLAYER_W && bally + BALL_H >= PLAYER_Y){return 1;}else{return 0;}
}
int ballColWithBorder(int ballx, int bally){
	if(ballx <= 0){return 1;}else if(ballx + BALL_W >= 80){return 2;}else{return 0;}
}
int ballColWithGround(int bally){
	if(bally+BALL_H>= 31){return 1;}else{return 0;}
}
int ballColWithTop(int bally){
	if(bally <= 0){return 1;}else{return 0;}
}

int doesPlayerWin(int map[MAP_W][MAP_H]){

	for(int i = 0; i < MAP_W;i++){
		for(int j = 0;j < MAP_H;j++){
			if(map[i][j]!=0)return 0;
		}
	}
	return 1;

}
//zoom
int ballColWithBrick(int ballx, int bally, int map[MAP_W][MAP_H]){
	int i = 0;
	int j = 0;
	if(bally <= MAP_H*2 + 1 && bally >= 1){
	//if(map[(int)(ballx/10+1)][(int)(bally/2 -1)] > 0){return 1;}else{return 0;}//système imparfait
		for(i = 0; i < MAP_W;i++){
			for(j = 0;j < MAP_H;j++){
				if(map[i][j] > 0 && (ballx >= i * BRICK_W || ballx + BALL_W >= i * BRICK_W) && ballx <= i * BRICK_W + BRICK_W && bally <= j*BRICK_H + BRICK_H + 1 && bally + BALL_W <= j*BRICK_H + 1){ // à refaire
					map[i][j]--;
					return 1;
				}else{
					continue;
				}
			}
		}
		return 0;	
	}else{
		return 0;
	}
}
