#include <stdio.h>
#include "displayBoard.c"
#include "initializeGame.c"

// Test here for now.
void playGame() {
	initializeGame();

	// I disabled this loop for now but this should be the final result
	/*
	do { 
		printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", (cur_player == 0 ? 'A' : 'B'));
		// int r1, c1, r2, c2;
		// if(getPlayerMove(&r1, &c1, &r2, &c2)) {
			// drawLine();
			// checkBox();
			// calculateScores();
			// switchTurn();
		}
		else {
			// print error message.
		}
	} while (!isGameOver()); */
}

int main() {
	playGame();
}