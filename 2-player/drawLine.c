#include "initializeGame.h"
#include "drawLine.h"

int drawLine(int r1, int c1, int r2, int c2) {
	// To draw horizontal line "-"
	if(fixedRow(r1, c1, r2, c2) == 1) {
		int row = 2 * r1;
		int col = c1 + c2;
		// If line not already drawn
		if(board[row][col] == ' ') {
			board[row][col] = '-';
			return 1;
		}
		// If line already drawn - edge case to be handled in getPlayerMove()
		else {
			return 0;
		}
	}

	// To draw vertical line "|"
	else if(fixedRow(r1, c1, r2, c2) == 2) {
		int row = r1 + r2;
		int col = 2 * c1;
		// If line not already drawn
		if(board[row][col] == ' ') {
			board[row][col] = '|';
			return 1;
		}
		// If line already drawn - edge case to be handled in getPlayerMove()
		else {
			return 0;
		}
	}
}