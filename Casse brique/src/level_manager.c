#include "level_manager.h"
int loadLevel(int map[MAP_W][MAP_H], char levelname[8]){

	char path[34];
	strcpy(path, "assets/levels/");
	strcat(path, levelname);
	strcat(path, LEVEL_EXT);
	FILE *f = fopen(path, "rb");
	unsigned char buffer[MAP_W*MAP_H + MAP_W];
	int k = 0, j = 0, i = 0;
	
	fread(buffer,sizeof(buffer),1,f); 
	
	for(j = 0;k < MAP_H*MAP_W+MAP_W;j++){
		if(buffer[k] == 's'){k++;i++;j=-1;}
		else{
			map[i][j] = buffer[k];
			k++;
		}
	}
	fclose(f);
}
int saveLevel(int map[MAP_W][MAP_H], char levelname[8]){

	char path[34];
	strcpy(path, "assets/levels/");
	strcat(path, levelname);
	strcat(path, LEVEL_EXT);
	FILE *f = fopen(path, "wb");
	unsigned char buffer[MAP_W*MAP_H + MAP_W];
	
	int k = 0;
	for(int i = 0;i < MAP_W;i++){
		for(int j = 0;j < MAP_H;j++){
			buffer[k] = map[i][j];
			k++;
		}
		buffer[k] = 's';
		k++;
	}
	fwrite(buffer,sizeof(buffer),1,f); 
	fclose(f);
}
