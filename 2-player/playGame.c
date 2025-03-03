#include <stdio.h>
#include "displayBoard.c"
#include "initializeGame.c"

// Test here for now.
void playGame() {
	initializeGame();
	board[0][4] = 1; 
    board[1][4] = 1; 
	displayBoard(board);

	// I disabled this loop for now but this should be the final result
	/* int num;
	do { 
		printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", (cur_player == 1 ? 'A' : 'B'));
		// getPlayerMove()
		// drawLine()
		// checkBox()
		// calculateScores()
		// switchTurn()
	} while (!isGameOver()); */
}

int main() {
	playGame();
}