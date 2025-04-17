 
#ifndef DRIVER_FUNCTIONS_H
#define DRIVER_FUNCTIONS_H

#define	ROW_SIZE 5
#define COL_SIZE 6
#define BOXES (ROW_SIZE * COL_SIZE)
//#include "botFunctions.h"


typedef struct {
    int score_a;
    int score_b;
    int no_boxes;
    int cur_player;
	char board[2 * ROW_SIZE - 1][2 * COL_SIZE - 1];
} GameState;

void initializeGame(GameState *state);
void twoPlayer(GameState *state);
void easyMode(GameState *state);
void mediumMode(GameState *state);
void hardMode(GameState *state);

#endif