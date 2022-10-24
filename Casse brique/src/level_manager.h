#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
int loadLevel(int map[MAP_W][MAP_H], char levelname[8]);
int saveLevel(int map[MAP_W][MAP_H], char levelname[8]);

#endif
