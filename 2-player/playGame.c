#include <stdio.h>
#include "playGame.h"

// Test here for now.
void playGame() {
	initializeGame();
	
	int input;
	do { 
		displayBoard();
		printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", (cur_player == 0 ? 'A' : 'B'));
		int r1, c1, r2, c2;
		getPlayerMove(&r1, &c1, &r2, &c2); // it calls drawLine() inside it
		printf("%d%d%d%d", r1, c1, r2, c2);
		// calculateScores(); // it calls both checkBox() and switchTurn() inside
	} while (1);

	// I disabled this loop for now but this should be the final result
	/*
	do { 
		printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", (cur_player == 0 ? 'A' : 'B'));
		int r1, c1, r2, c2;
		getPlayerMove(&r1, &c1, &r2, &c2);
		printf("%d%d%d%d", r1, c1, r2, c2);
		calculateScores(); // it calls both checkBox() and switchTurn() inside
	} while (!isGameOver()); */
	
}

int main() {
	playGame();
}