#include "tempHard.h"

int flag = 0;

int boxes[4] = {20, 0, 0, 0};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}


// A function to determine the game phase (opening, midgame, endgame) to determine which algorithm to play.
GamePhase getGamePhase(GameState *state) {
    //if((boxes[0] + boxes[1]) == 0 || state->no_boxes >= 0.8 * BOXES)
    //    return ENDGAME;
    if((boxes[0] + boxes[1]) >= 0.6 * (BOXES - state->no_boxes))
        return OPENING;
    else return MIDGAME;
}


// A function for opening (when the boxes with 0 or 1 edges >= 60% of the empty boxes).
void generateSafeMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
    typedef struct {
        int r1, c1, r2, c2, row, col;
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


                int box_left = countEdges(state, row - 1, col);   // box above
                int box_right = countEdges(state, row + 1, col);  // box below


                if ((box_left < 3) && (box_right < 3)) {
                    safe_moves[safe_count++] = (Move){r, c1_temp, r, c2_temp, row, col};
                }


                state->board[row][col] = ' '; // undo
            }


            // c for vertical line
            if (row % 2 == 1 && col % 2 == 0) {
                int c = col / 2;
                int r1_temp = (row - 1) / 2;
                int r2_temp = (row + 1) / 2;


                state->board[row][col] = '|';


                int boxTop = countEdges(state, row, col - 1);   // box left
                int boxBottom = countEdges(state, row, col + 1); // box right


                if ((boxTop < 3) && (boxBottom < 3)) {
                    safe_moves[safe_count++] = (Move){r1_temp, c, r2_temp, c, row, col};
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
		boxes[countEdges(state, safe_moves[pick].row, safe_moves[pick].col)]--;
        drawLine(state, *r1, *c1, *r2, *c2);
		boxes[countEdges(state, safe_moves[pick].row, safe_moves[pick].col)]++;
		
    }
}


// Helper function to evaluate the board for minimax.


// same loop as generateMediumMove
/*
 Heuristics:
 +2 for bot box
-2 for opponent box
-1 for 3-edged boxes (danger)
+1 for 1-edged boxes (potential chain)
*/
int evaluateBoard(GameState *state) {
    int eval = 0;
    int max_row = 2 * ROW_SIZE - 1;
    int max_col = 2 * COL_SIZE - 1;
   
    // Iterate over each box center (at odd indices).
    for (int row = 1; row < max_row; row += 2) {
        for (int col = 1; col < max_col; col += 2) {
            char boxMark = state->board[row][col];
            if (boxMark == 'A') {
                // Opponent's box: subtract 2 points.
                eval -= 2;
            } else if (boxMark == 'B') {
                // Bot's box: add 2 points.
                eval += 2;
            } else {
                // Unclaimed box: count the drawn edges.
                int edgeCount = countEdges(state, row, col);
                if (edgeCount == 3) {
                    // A nearly complete box is dangerous.
                    eval -= 1;
                } else if (edgeCount == 1) {
                    // A box with one edge is a potential chain.
                    eval += 1;
                }
            }
        }
    }
    return eval;
}






////}


// minimax Algorithm Body.
int minimax(GameState *state, int depth, bool bot, int alpha, int beta) {
    // In case recursion is finished OR the game has ended!
    if (depth == 0 || state->no_boxes == (ROW_SIZE - 1) * (COL_SIZE - 1)) {
        return evaluateBoard(state);
    }


    int best_score = (bot ? INT_MIN : INT_MAX);


    for (int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
        for (int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
            if (state->board[row][col] != ' ') continue;
            int r1, c1, r2, c2;
            if (row % 2 == 0 && col % 2 == 1) {
                r1 = r2 = row / 2;
                c1 = (col - 1) / 2;
                c2 = c1 + 1;
            } else if (row % 2 == 1 && col % 2 == 0) {
                c1 = c2 = col / 2;
                r1 = (row - 1) / 2;
                r2 = r1 + 1;
            } else continue;


            // Create a copy of the current board.
            GameState newState = *state;


            if (!drawLine(&newState, r1, c1, r2, c2)) continue;


            calculateScores(&newState, r1, c1, r2, c2);


            bool is_bot = (newState.cur_player == 1);
            int result = minimax(&newState, depth - 1, is_bot, alpha, beta);


            if (bot) {
                best_score = max(best_score, result);
                alpha = max(alpha, result);
            } else {
                best_score = min(best_score, result);
                beta = min(beta, result);
            }


            if (beta <= alpha)
                return best_score;  // prune
        }
    }


    return best_score;
}






// A function for Mid-game.


void generateMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
	if(flag == 0) {
		printf("In midgame\n");
		flag = 1;
	}
		
    int bestEval = INT_MIN;
    int bestMove[6] = { -1, -1, -1, -1 , -1, -1};


   
    for (int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
        for (int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
         
            if (state->board[row][col] != ' ') continue;


            int r1, c1, r2, c2;
            // Determine the move type based on board cell indices.
            if (row % 2 == 0 && col % 2 == 1) {
               
                r1 = r2 = row / 2;
                c1 = (col - 1) / 2;
                c2 = c1 + 1;
            } else if (row % 2 == 1 && col % 2 == 0) {
               
                c1 = c2 = col / 2;
                r1 = (row - 1) / 2;
                r2 = r1 + 1;
            } else {
                continue;
            }


            // Create a copy of the current game state to simulate the move.
            GameState tempState = *state;
            if (!drawLine(&tempState, r1, c1, r2, c2))
                continue; // Skip if the move is invalid meaning line already drawn.


         
            calculateScores(&tempState, r1, c1, r2, c2);


            // Determine whose turn it is after the move.
            bool nextBotTurn = (tempState.cur_player == 1);


            // Evaluate this move using minimax.
            int eval = minimax(&tempState, DEPTH - 1, nextBotTurn, INT_MIN, INT_MAX);


            // Keep track if this move is the best so far.
            if (eval > bestEval) {
                bestEval = eval;
                bestMove[0] = r1;
                bestMove[1] = c1;
                bestMove[2] = r2;
                bestMove[3] = c2;
				bestMove[4] = row;
				bestMove[5] = col;
            }
        }
    }


    if (bestMove[0] != -1) {
        // A valid move was found. Set output parameters and draw the move.
        *r1 = bestMove[0];
        *c1 = bestMove[1];
        *r2 = bestMove[2];
        *c2 = bestMove[3];
		boxes[countEdges(state, bestMove[4], bestMove[5])]--;
        drawLine(state, *r1, *c1, *r2, *c2);
		boxes[countEdges(state, bestMove[4], bestMove[5])]++;
       
    }
}








// A function for End-game (when all chains are formed).
void generateParityChainMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {


}


// The main function to generate hard move.
void generateHardMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
	
    GamePhase phase = getGamePhase(state);
	printf("%d %d %d %d", boxes[0], boxes[1], boxes[2], boxes[3]);
    if (phase == OPENING) {
        generateSafeMove(state, r1, c1, r2, c2);
    }
	else {
        generateMinimaxMove(state, r1, c1, r2, c2);
	}
    //} else if (phase == ENDGAME) {
    //    generateParityChainMove(state, r1, c1, r2, c2);
    //}
}
