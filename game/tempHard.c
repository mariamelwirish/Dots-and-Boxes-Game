#include "tempHard.h"

// A function to determine the game phase (opening, midgame, endgame) to determine which algorithm to play.
GamePhase getGamePhase() {
	if((boxes[0] + boxes[1]) == 0 || no_boxes >= 0.8 * BOXES) 
		return ENDGAME;
	else if((boxes[0] + boxes[1]) >= 0.6 * (BOXES - no_boxes)) 
		return OPENING;
	else return MIDGAME;
}

// A function for opening (when the boxes with 0 or 1 edges >= 60% of the empty boxes).
void generateSafeMove(int *r1, int *c1, int *r2, int *c2) {
    typedef struct {
        int r1, c1, r2, c2;
    } Move;

    Move safe_moves[200];  // store safe moves
    int safe_count = 0;

    for (int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
        for (int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
            if (board[row][col] != ' ') continue;

            // check for horizontal line
            if (row % 2 == 0 && col % 2 == 1) {
                int r = row / 2;
                int c1_temp = (col - 1) / 2;
                int c2_temp = (col + 1) / 2;

                // simulate move
                board[row][col] = '-';

                int box_left = countEdges(row - 1, col);   // box above
                int box_right = countEdges(row + 1, col);  // box below

                if ((box_left < 3) && (box_right < 3)) {
                    safe_moves[safe_count++] = (Move){r, c1_temp, r, c2_temp};
                }

                board[row][col] = ' '; // undo
            }

            // c for vertical line
            if (row % 2 == 1 && col % 2 == 0) {
                int c = col / 2;
                int r1_temp = (row - 1) / 2;
                int r2_temp = (row + 1) / 2;

                board[row][col] = '|';

                int boxTop = countEdges(row, col - 1);   // box left
                int boxBottom = countEdges(row, col + 1); // box right

                if ((boxTop < 3) && (boxBottom < 3)) {
                    safe_moves[safe_count++] = (Move){r1_temp, c, r2_temp, c};
                }

                board[row][col] = ' '; // undo
            }
        }
    }

    if (safe_count > 0) {
        int pick = rand() % safe_count;
        *r1 = safe_moves[pick].r1;
        *c1 = safe_moves[pick].c1;
        *r2 = safe_moves[pick].r2;
        *c2 = safe_moves[pick].c2;
        drawLine(*r1, *c1, *r2, *c2);
    }
}

// Helper function to evaluate the board for minimax.
int evaluateBoard() {

}

// minimax Algorithm Body.
// Need to replace player with struct (later after modification).
int minimax(int depth, int alpha, int beta, int player) {

}


// A function for Mid-game.
void generateMinimaxMove(int *r1, int *c1, int *r2, int *c2) {

}

// A function for End-game (when all chains are formed).
void generateParityChainMove(int *r1, int *c1, int *r2, int *c2) {

}

// The main function to generate hard move.
void generateHardMove(int *r1, int *c1, int *r2, int *c2) {
	GamePhase phase = getGamePhase();
    if (phase == OPENING) {
        generateSafeMove(r1, c1, r2, c2);
    } else if (phase == MIDGAME) {
        generateMinimaxMove(r1, c1, r2, c2); 
    } else if (phase == ENDGAME) {
        generateParityChainMove(r1, c1, r2, c2);
    }
}