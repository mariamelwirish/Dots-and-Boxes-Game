#include <stdio.h>
#include "initializeGame.h"

void initializeGame() {
	// Setting up the board.
	for(int row = 0; row < ROW_SIZE * 2 - 1; row++) {
		for(int col = 0; col < COL_SIZE * 2 - 1; col++) {
			if(row % 2 == 0 && col % 2 == 0) 
				board[row][col] = '.';
			else if(row % 2 == 0 && col % 2 == 1)
				board[row][col] = ' ';
			else
				board[row][col] = ' ';
		}
	}

	// Setting scores to 0.
	scores[0] = 0;
	scores[1] = 0;

	// Player 1 starts.
	cur_player = 0;

	// Number of boxes = 0
	no_boxes = 0;
}