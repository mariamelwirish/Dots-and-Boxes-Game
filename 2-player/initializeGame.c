#include <stdio.h>
#include "initializeGame.h"


void initializeGame() {
	// Setting up the board.
	for(int row = 0; row < 2 * ROW_SIZE - 1; row++) {
		for(int col = 0; col < 2 * COL_SIZE - 1; col++) {
			board[row][col] = 0;
		}
	}

	// Setting scores to 0.
	scores[0] = 0;
	scores[1] = 0;

	// Player 1 starts.
	cur_player = 1;
}