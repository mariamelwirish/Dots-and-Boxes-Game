#ifndef INITIALIZE_GAME_H
#define INITIALIZE_GAME_H

#define	ROW_SIZE 5
#define COL_SIZE 6

int cur_player;
int board[2 * ROW_SIZE - 1][2 * COL_SIZE - 1];
int scores[2];

void initializeGame(void);

#endif