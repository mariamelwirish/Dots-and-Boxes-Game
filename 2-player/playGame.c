#include <stdio.h>
#include "displayBoard.c"
#include "initializeGame.c"

// Test here for now.
void playGame() {
	initializeGame();
	board[0][4] = 1; 
    board[1][4] = 1; 
	displayBoard(board);
}

int main() {
	playGame();
}