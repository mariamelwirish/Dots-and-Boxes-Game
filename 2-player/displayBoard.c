#include <stdio.h>
#include "initializeGame.h"

void displayBoard() {
	// Printing the numbers on the top (0 - 5)
	printf("  ");
	for(int num = 0; num < COL_SIZE * 2 - 1; num++) {
		if(num % 2 == 0)
			printf("%d", num / 2);
		else 
			printf(" ");
	}
	printf("\n");

	// Printing the grid & row numbers
	for(int row = 0; row < ROW_SIZE * 2 - 1; row ++) {
		// For printing the row numbers
		if(row % 2 == 0)
			printf("%d ", row / 2);
		else 
			printf("  ");

		// Printing the grid elements
		for(int col = 0; col < COL_SIZE * 2 - 1; col++) {
			printf("%c", board[row][col]);
		}
		printf("\n");
	}
}