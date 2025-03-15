#include "driverFunctions.h"

void initializeGame() {
	// Setting up the board.
	for(int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
		for(int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
			if(row % 2 == 0 && col % 2 == 0) 
				board[row][col] = '.';
			else if(row % 2 == 0 && col % 2 == 1)
				board[row][col] = ' ';
			else
				board[row][col] = ' ';
		}
	}

	// Setting scores to 0.
	score_a = 0;
	score_b = 0;

	// Player 1 starts.
	cur_player = 0;

	// Number of boxes = 0
	no_boxes = 0;
}

// the main function to run the game - called in main.c
void twoPlayer() {
	initializeGame();
	do { 
		displayBoard();
		printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", (cur_player == 0 ? 'A' : 'B'));
		int r1, c1, r2, c2;
		getPlayerMove(&r1, &c1, &r2, &c2);
		calculateScores(r1, c1, r2, c2);
		printf("******************************************************************************\n");
		printf("Player A score: %d\n", score_a);
		printf("Player B score: %d\n", score_b);
		printf("******************************************************************************\n");
	} while (!isGameOver());
	
}
