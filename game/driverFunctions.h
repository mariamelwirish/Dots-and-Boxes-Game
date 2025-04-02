 
#ifndef DRIVER_FUNCTIONS_H
#define DRIVER_FUNCTIONS_H

#define	ROW_SIZE 5
#define COL_SIZE 6
#include "botFunctions.h"

int cur_player;
char board[2 * ROW_SIZE - 1][2 * COL_SIZE - 1];
int score_a, score_b;
int no_boxes;

void initializeGame(void);
void twoPlayer(void);
void easyMode(void);
void mediumMode(void);

#endif