#include "botFunctions.h"

void generateEasyMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
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
	} while(drawLine(state, *r1, *c1, *r2, *c2) == 0); // to ensure that the line is not already drawn
}

// Helper function for medium mode to generate random move on a box with 0 or 1 edges.
void drawRandomLine(GameState *state, int *r1, int *c1, int *r2, int *c2, int row, int col) {
	int flag = rand() % 2; // choose random edge -> flag = 0 means '-' & flag = 1 = means '|'.
	if(flag == 0) { // '-'
		int flag_row; // choose direction -> 0 = down, 1 = up
		if(state->board[row + 1][col] != ' ') // down is taken. forced to draw up.
			flag_row = 1;
		else if(state->board[row - 1][col] != ' ') // up is taken. forced to draw down
			flag_row = 0;
		else // if both available, decide randomly
			flag_row = rand() % 2;
		if(flag_row == 0) *r1 = (row + 1) / 2;
		else *r1 = (row - 1) / 2;
		*r2 = *r1;
		*c1 = (col - 1) / 2;
		*c2 = (col + 1) / 2;
	}
	
	else if(flag == 1) { // '|'
		int flag_col = -1; // 0 = right, 1 = left
		if(state->board[row + 1][col] != ' ') // right is taken. forced to draw left.
			flag_col = 1;
		else if(state->board[row - 1][col] != ' ') // left is taken. forced to draw right.
			flag_col = 0;
		else
			flag_col = rand() % 2;
		if(flag_col == 0) *c1 = (col + 1) / 2;
		else *c1 = (col - 1) / 2;
		*c2 = *c1;
		*r1 = (row - 1) / 2;
		*r2 = (row + 1) / 2;
	}
	
	drawLine(state, *r1, *c1, *r2, *c2);
}

// Helper function to count the edges on a box.
int countEdges(GameState *state, int row, int col) {
	int count = 0;
	count += (state->board[row + 1][col] != ' ' ? 1 : 0);
	count += (state->board[row - 1][col] != ' ' ? 1 : 0);
	count += (state->board[row][col + 1] != ' ' ? 1 : 0);
	count += (state->board[row][col - 1] != ' ' ? 1 : 0);
	return count;
}

void generateMediumMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
	// alt_row & alt_col if in case there are no winning moves, we choose boxes with 0 or 1 edges.
    int alt_row = -1, alt_col = -1;
    for (int row = 1; row < 2 * ROW_SIZE - 1; row += 2) {
        for (int col = 1; col < 2 * COL_SIZE - 1; col += 2) {
			// if the box is not closed yet.
            if (state->board[row][col] == ' ') {
				// count the edges of the box.
                int count = countEdges(state, row, col);
				// There is a winning move!
                if (count == 3) {
					// need to decide which edge is missing.
                    if (state->board[row + 1][col] == ' ') { // Top edge missing
                        *r1 = (row + 1) / 2;
                        *r2 = (row + 1) / 2;
                        *c1 = (col - 1) / 2;
                        *c2 = (col + 1) / 2;
                        drawLine(state, *r1, *c1, *r2, *c2);
                    } else if (state->board[row - 1][col] == ' ') { // Bottom edge missing
                        *r1 = (row - 1) / 2;
                        *r2 = (row - 1) / 2;
                        *c1 = (col - 1) / 2;
                        *c2 = (col + 1) / 2;
                        drawLine(state, *r1, *c1, *r2, *c2);
                    } else if (state->board[row][col + 1] == ' ') { // Left edge missing
                        *r1 = (row - 1) / 2;
                        *r2 = (row + 1) / 2;
                        *c1 = (col + 1) / 2;
                        *c2 = (col + 1) / 2;
                        drawLine(state, *r1, *c1, *r2, *c2);
                    } else if (state->board[row][col - 1] == ' ') { // Right edge missing
                        *r1 = (row - 1) / 2;
                        *r2 = (row + 1) / 2;
                        *c1 = (col - 1) / 2;
                        *c2 = (col - 1) / 2;
                        drawLine(state, *r1, *c1, *r2, *c2);
                    }
					return;
                }
				// No winning moves. At least don't help the opponent!
				// Priotrize boxes with 0 edges (less risky).
                else if (count == 0) {
                    alt_row = row;
					alt_col = col;
                }
				// No boxes with 0 edges found? Second priority: boxes with 1 edge.
				else if (alt_row == -1 && alt_col == -1 && count == 1) {
                    alt_row = row;
					alt_col = col;
                }
            }
        }
    }

	// If there is no winning move and there are boxes with 0 or 1 edges.
    if (alt_row != -1) {
       drawRandomLine(state, r1, c1, r2, c2, alt_row, alt_col);
		return;
    }

	// If all the options are either boxes with 2 edges or closed boxes. Doesn't matter; play random move.
    generateEasyMove(state, r1, c1, r2, c2);
}
