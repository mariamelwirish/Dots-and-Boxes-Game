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
	typedef struct {
        int r1, c1, r2, c2;
    } Move;

    Move safe_moves[200];  // store safe moves
    int safe_count = 0;

    for (int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
        for (int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
            if (state->board[row][col] != ' ') continue;

            // check for horizontal line
            if (row % 2 == 0 && col % 2 == 1) {
                int r = row / 2;
                int c1_temp = (col - 1) / 2;
                int c2_temp = (col + 1) / 2;

                // simulate move
                state->board[row][col] = '-';
                int box_up = (row == 0 ? -1 : countEdges(state, row - 1, col));   // box above
                int box_down = (row == 2 * (ROW_SIZE - 1)? -1 : countEdges(state, row + 1, col));  // box below

                if(box_up == 4 || box_down == 4) {
					*r1 = r;
					*c1 = c1_temp;
					*r2 = r;
					*c2 = c2_temp;
					return;
				}
				else if ((box_up < 3) && (box_down < 3)) {
                    safe_moves[safe_count++] = (Move){r, c1_temp, r, c2_temp};
				}

                state->board[row][col] = ' '; // undo
            }


            // c for vertical line
            if (row % 2 == 1 && col % 2 == 0) {
                int c = col / 2;
                int r1_temp = (row - 1) / 2;
                int r2_temp = (row + 1) / 2;

                state->board[row][col] = '|';
                int box_left = (col == 0 ? -1 : countEdges(state, row, col - 1));   // box left
                int box_right = (col == 2 * (COL_SIZE - 1) ? -1 : countEdges(state, row, col + 1)); // box right

				if(box_left == 4 || box_right == 4) {
					*c1 = c;
					*c2 = c;
					*r1 = r1_temp;
					*r2 = r2_temp;
					return;
				}
                else if ((box_left < 3) && (box_right < 3)) {
                    safe_moves[safe_count++] = (Move){r1_temp, c, r2_temp, c};
                }

                state->board[row][col] = ' '; // undo
            }
        }
    }

    if (safe_count > 0) {
        int pick = rand() % safe_count;
        *r1 = safe_moves[pick].r1;
        *c1 = safe_moves[pick].c1;
        *r2 = safe_moves[pick].r2;
        *c2 = safe_moves[pick].c2;
        drawLine(state, *r1, *c1, *r2, *c2);
    }
	else {
		generateEasyMove(state, r1, c1, r2, c2);
	}
}
