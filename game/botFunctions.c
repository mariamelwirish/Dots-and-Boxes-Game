#include "botFunctions.h"

void generateEasyMove(int *r1, int *c1, int *r2, int *c2) {
	do {
		int flag = rand() % 2; // random flag to select whether to draw horizontal (flag = 0) or vertical line (flag = 1)
		// if the line is "-". i.e. row is fixed
		if(flag == 0) {
			*r1 = rand() % ROW_SIZE;  // generate random row within range [0, ROW_SIZE - 1]
			*r2 = *r1; 
			*c1 = rand() % COL_SIZE; // generate random column [0, COL_SIZE - 1]
			int flagMove; // flag to decide whether to go right (flag = 0) or left (flag = 1)
			if(*c1 == 0) flagMove = 0; // if we are on the left edge, hard code the flag to go to right
			else if(*c1 == COL_SIZE - 1) flagMove = 1; // same with right edge
			else flagMove = rand() % 2; // else if we are in the middle, decide randomly
			*c2 = (flagMove == 0 ? *c1 + 1 : *c1 - 1); 
		}
		// if the line is "|". i.e. vertical line
		else {
			*c1 = rand() % COL_SIZE; 
			*c2 = *c1;
			*r1 = rand() % ROW_SIZE;
			int flagMove;
			if(*r1 == 0) flagMove = 0;
			else if(*r1 == ROW_SIZE - 1) flagMove = 1;
			else flagMove = rand() % 2;
			*r2 = (flagMove == 0 ? *r1 + 1 : *r1 - 1);
		}
	} while(drawLine(*r1, *c1, *r2, *c2) == 0); // to ensure that the line is not already drawn
}

// Helper function for medium mode to generate random move on a box with 0 or 1 edges.
void drawRandomLine(int row, int col) {
	
}

// Helper function to count the edges on a box.
int countEdges(int row, int col) {
	
}

void generateMediumMove(int *r1, int *c1, int *r2, int *c2) {
    int alt_row = -1, alt_col = -1;

    for (int row = 1; row < 2 * ROW_SIZE - 1; row += 2) {
        for (int col = 1; col < 2 * COL_SIZE - 1; col += 2) {
            if (board[row][col] == ' ') {
                int count = countEdges(row, col);
                if (count == 3) {
                    if (board[row + 1][col] == ' ') { // Top side missing
                        *r1 = (row + 1) / 2;
                        *r2 = (row + 1) / 2;
                        *c1 = (col - 1) / 2;
                        *c2 = (col + 1) / 2;
                        drawLine(*r1, *c1, *r2, *c2);
                        return;
                    } else if (board[row - 1][col] == ' ') { // Bottom side missing
                        *r1 = (row - 1) / 2;
                        *r2 = (row - 1) / 2;
                        *c1 = (col - 1) / 2;
                        *c2 = (col + 1) / 2;
                        drawLine(*r1, *c1, *r2, *c2);
                        return;
                    } else if (board[row][col + 1] == ' ') { // Left side missing
                        *r1 = (row - 1) / 2;
                        *r2 = (row + 1) / 2;
                        *c1 = (col + 1) / 2;
                        *c2 = (col + 1) / 2;
                        drawLine(*r1, *c1, *r2, *c2);
                        return;
                    } else if (board[row][col - 1] == ' ') { // Right side missing
                        *r1 = (row - 1) / 2;
                        *r2 = (row + 1) / 2;
                        *c1 = (col - 1) / 2;
                        *c2 = (col - 1) / 2;
                        drawLine(*r1, *c1, *r2, *c2);
                        return;
                    }
                }
                else if (alt_row == -1 && alt_col == -1 && count == 0) {
                    alt_row = row;
					alt_col = col;
                }
				else if (alt_row == -1 && alt_col == -1 && count == 0) {
                    alt_row = row;
					alt_col = col;
                }
            }
        }
    }

    if (alt_row != -1) {
       drawRandomLine(alt_row, alt_col);
		return;
    }

    generateEasyMove(r1, c1, r2, c2);
}
