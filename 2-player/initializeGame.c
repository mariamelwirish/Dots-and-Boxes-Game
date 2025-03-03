#include <stdio.h>
#include "initializeGame.h"


void initializeGame() {
	// Setting up the board.
	for(int row = 0; row < ROW_SIZE; row++) {
		for(int col = 0; col < COL_SIZE; col++) {
			board[row][col] = 0;
		}
	}

	// Setting scores to 0.
	scores[0] = 0;
	scores[1] = 0;

	// Player 1 starts.
	cur_player = 1;

	// Number of boxes  = 0
	no_boxes = 0;
}