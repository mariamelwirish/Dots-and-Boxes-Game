#include <stdio.h>
#include "displayBoard.c"
#include "initializeGame.c"
#include "drawLine.c"

// Test here for now.
void playGame() {
	initializeGame();
	// First 5 tests - static input for now till we develop getPlayerMove()
	drawLine(0, 4, 0, 3);
	drawLine(0, 4, 1, 4);
	drawLine(0, 5, 1, 5);
	drawLine(1, 3, 1, 4);
	drawLine(0, 3, 1, 3);
	displayBoard();
	// I disabled this loop for now but this should be the final result
	/*
	do { 
		printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", (cur_player == 0 ? 'A' : 'B'));
		// int r1, c1, r2, c2;
		// if(getPlayerMove(&r1, &c1, &r2, &c2)) {
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