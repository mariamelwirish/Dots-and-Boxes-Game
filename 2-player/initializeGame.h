#ifndef INITIALIZE_GAME_H
#define INITIALIZE_GAME_H

#define	ROW_SIZE 5
#define COL_SIZE 6

int cur_player;
int board[ROW_SIZE][COL_SIZE];
int scores[2];

void initializeGame(void);

#endif