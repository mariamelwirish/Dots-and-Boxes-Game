#include "headers.h"


/**
 * void generateEasyMove(GameState *state, int *r1, int *c1, int *r2, int *c2)
 *
 * Requires:
 *      - state != NULL
 *      - The board within state must be initialized using initializeGame.
 *      - The pointers r1, c1, r2, and c2 must be valid and not NULL.
 *
 * Effects:
 *      - Randomly generates a move for the easy-level bot.
 *      - The move is either horizontal or vertical and is randomly selected.
 *      - Ensures the chosen move is valid meaning not already drawn.
 *      - Updates the board by drawing the selected line.
 *
 * Returns:
 *      - The function does not return a value but updates the r1, c1, r2, c2 coordinates
 *        to reflect the selected move.
 *      - The board is modified by placing a '-' or '|' character.
 */


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

/**
 * void generateMediumMove(GameState *state, int *r1, int *c1, int *r2, int *c2)
 *
 * Requires:
 *      - state != NULL
 *      - The game board must be initialized and contain valid characters.
 *      - The pointers r1, c1, r2, and c2 must be valid.
 *
 * Effects:
 *      - Scans the board for all potential safe moves ,those being that they dont add a third edge.
 *      - Prioritizes capturing boxes that are already surrounded by 3 edges by adding the fourth and completing the box..
 *      - If no such move exists, selects randomly from a list of safe moves those that add a single edge or two.
 *      - Falls back to generateEasyMove if no safe move is found.
 *      - Updates the board with the selected move.
 *
 * Returns:
 *      - Updates r1, c1, r2, c2 with the coordinates of the chosen move.
 *      - The board is modified with the drawn line.
 */



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

char my_char = ' ', opp_char = ' ';
int my_turn = -1;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

/**
 * GamePhase getGamePhase(GameState *state)
 *
 * Requires:
 *      - state != NULL
 *      - The state->moves counter must be correctly incremented throughout the game.
 *
 * Effects:
 *      - Analyzes the current number of moves to determine the phase of the game.
 *
 * Returns:
 *      - OPENING if the game is in the first 15% of total moves.
 *      - MIDGAME otherwise.
 */


// A function to determine the game phase (opening, midgame) to determine which algorithm to play.
GamePhase getGamePhase(GameState *state) {
    if (state->moves <= (0.15 * TOTAL_MOVES)) {
        return OPENING;
    }
    else {
        return MIDGAME;
    }
}

// Helper function to evaluate the board for minimax.
int evaluateBoard(GameState *state) {
    int eval = 0;
    int max_row = 2 * ROW_SIZE - 1;
    int max_col = 2 * COL_SIZE - 1;

    for (int row = 1; row < max_row; row += 2) {
        for (int col = 1; col < max_col; col += 2) {
            char boxMark = state->board[row][col];
            if (boxMark == my_char) eval += 2;
            else if (boxMark == opp_char) eval -= 2;
            else {
                int edgeCount = countEdges(state, row, col);
                if (edgeCount == 3) {
                    eval -= 2;
                } else if (edgeCount == 1) {
                    eval += 2;
                } else if (edgeCount == 2) {
                    eval += 1;
                }
            }

        }
    }
    return eval + 2 * (state->scores[my_turn] - state->scores[!my_turn]);
}
/**
 * int minimax(GameState *state, int depth, bool bot, int alpha, int beta)
 *
 * Requires:
 *      - state != NULL
 *      - depth >= 0
 *      - alpha and beta are valid initial bounds for pruning.
 *
 * Effects:
 *      - Performs minimax search with alpha-beta pruning to a given depth.
 *      - Simulates moves and recursively evaluates the board using evaluateBoard.
 *
 * Returns:
 *      - The best evaluation score reachable from the current state.
 *      - Maximizes score for bot, minimizes for opponent.
 */

// Minimax algorithm with alpha-beta pruning
int minimax(GameState *state, int depth, bool bot, int alpha, int beta) {
    if (depth == 0 || state->no_boxes == (ROW_SIZE - 1) * (COL_SIZE - 1))
        return evaluateBoard(state);

    int best_score = bot ? INT_MIN : INT_MAX;

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

            GameState newState = *state;
            if (!drawLine(&newState, r1, c1, r2, c2)) continue;

            calculateScores(&newState, r1, c1, r2, c2);
            bool is_bot = (newState.cur_player == my_turn);
            int result = minimax(&newState, depth - 1, is_bot, alpha, beta);

            if (bot) {
                best_score = max(best_score, result);
                alpha = max(alpha, result);
            } else {
                best_score = min(best_score, result);
                beta = min(beta, result);
            }

            if (beta <= alpha && best_score != INT_MAX && best_score != INT_MIN) return best_score;
        }
    }

    return best_score;
}


/**
 * void generateMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2)
 *
 * Requires:
 *      - state != NULL
 *      - r1, c1, r2, c2 are valid pointers.
 *      - DEPTH must be defined globally.
 *
 * Effects:
 *      - Iterates through all valid moves and applies minimax to each one.
 *      - Selects the move with the highest minimax score.
 *      - Updates the board with the best move found.
 *
 * Returns:
 *      - Updates r1, c1, r2, c2 with the coordinates of the best move.
 *      - The board is updated with the selected move.
 */

// Move generator using minimax
void generateMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
    my_turn = state->cur_player;
    my_char = (my_turn == 0) ? 'A' : 'B';
    opp_char = (my_turn == 0) ? 'B' : 'A';
    int bestEval = INT_MIN;
    int bestMove[4] = {-1, -1, -1, -1};

    for (int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
        for (int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
            if (state->board[row][col] != ' ') continue;

            int r1_temp, c1_temp, r2_temp, c2_temp;
            if (row % 2 == 0 && col % 2 == 1) {
                r1_temp = r2_temp = row / 2;
                c1_temp = (col - 1) / 2;
                c2_temp = c1_temp + 1;
            } else if (row % 2 == 1 && col % 2 == 0) {
                c1_temp = c2_temp = col / 2;
                r1_temp = (row - 1) / 2;
                r2_temp = r1_temp + 1;
            } else continue;

            GameState tempState = *state;
            if (!drawLine(&tempState, r1_temp, c1_temp, r2_temp, c2_temp)) continue;

            calculateScores(&tempState, r1_temp, c1_temp, r2_temp, c2_temp);
            bool nextBotTurn = (tempState.cur_player == my_turn);
            int eval = minimax(&tempState, DEPTH - 1, nextBotTurn, INT_MIN, INT_MAX);

            if (eval > bestEval) {
                bestEval = eval;
                bestMove[0] = r1_temp;
                bestMove[1] = c1_temp;
                bestMove[2] = r2_temp;
                bestMove[3] = c2_temp;
            }
        }
    }

    if (bestMove[0] != -1) {
        *r1 = bestMove[0];
        *c1 = bestMove[1];
        *r2 = bestMove[2];
        *c2 = bestMove[3];
        drawLine(state, *r1, *c1, *r2, *c2);
    }
}

// for multithreading
typedef struct {
    GameState state;
    int r1, c1, r2, c2;
    int score;
    bool is_valid;
} MinimaxThreadData;

// used in generateParallelMinimaxMove
void *evaluateMoveThread(void *arg) {
    MinimaxThreadData *data = (MinimaxThreadData *)arg;
    if (!drawLine(&data->state, data->r1, data->c1, data->r2, data->c2)) {
        data->is_valid = false;
        data->score = INT_MIN;
        return NULL;
    }

    calculateScores(&data->state, data->r1, data->c1, data->r2, data->c2);
    bool next_bot = (data->state.cur_player == my_turn);
    data->score = minimax(&data->state, DEPTH - 1, next_bot, INT_MIN, INT_MAX);
    data->is_valid = true;
    return NULL;
}


/**
 * void generateParallelMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2)
 *
 * Requires:
 *      - state != NULL
 *      - PTHREADS and DEPTH must be defined globally.
 *      - r1, c1, r2, c2 are valid pointers.
 *
 * Effects:
 *      - Launches multiple threads to evaluate minimax scores in parallel.
 *      - Each thread simulates one possible move and computes its score.
 *      - Selects the move with the highest score from all valid threads.
 *
 * Returns:
 *      - Updates r1, c1, r2, c2 with the best evaluated move.
 *      - The board is modified with the chosen move.
 */

// generateMinimax multithreaded edition
void generateParallelMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
    my_turn = state->cur_player;
    my_char = (my_turn == 0) ? 'A' : 'B';
    opp_char = (my_turn == 0) ? 'B' : 'A';
    pthread_t threads[THREADS];
    MinimaxThreadData thread_data[THREADS];
    int thread_count = 0;
    for (int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
        for (int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
            if (state->board[row][col] != ' ') continue;

            int tr1, tc1, tr2, tc2;
            if (row % 2 == 0 && col % 2 == 1) {
                tr1 = tr2 = row / 2;
                tc1 = (col - 1) / 2;
                tc2 = tc1 + 1;
            } else if (row % 2 == 1 && col % 2 == 0) {
                tc1 = tc2 = col / 2;
                tr1 = (row - 1) / 2;
                tr2 = tr1 + 1;
            } else continue;

            if (thread_count >= THREADS) continue; // prevent overflow

            MinimaxThreadData *data = &thread_data[thread_count];
            data->state = *state;
            data->r1 = tr1;
            data->c1 = tc1;
            data->r2 = tr2;
            data->c2 = tc2;
            data->score = INT_MIN;
            data->is_valid = false;

            pthread_create(&threads[thread_count], NULL, evaluateMoveThread, data);
            thread_count++;
        }
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    int best_eval = INT_MIN;
    int best_index = -1;
    for (int i = 0; i < thread_count; i++) {
        if (thread_data[i].is_valid && thread_data[i].score > best_eval) {
            best_eval = thread_data[i].score;
            best_index = i;
        }
    }

    if (best_index != -1) {
        *r1 = thread_data[best_index].r1;
        *c1 = thread_data[best_index].c1;
        *r2 = thread_data[best_index].r2;
        *c2 = thread_data[best_index].c2;
        drawLine(state, *r1, *c1, *r2, *c2);
    }
}


/**
 * void generateHardMove(GameState *state, int *r1, int *c1, int *r2, int *c2)
 *
 * Requires:
 *      - state != NULL
 *      - r1, c1, r2, c2 are valid pointers.
 *
 * Effects:
 *      - Determines the current game phase using getGamePhase.
 *      - In the OPENING phase, uses generateMediumMove for safety.
 *      - In the MIDGAME phase, applies generateParallelMinimaxMove for optimal move.
 *
 * Returns:
 *      - Updates r1, c1, r2, c2 with the selected move coordinates.
 *      - The board is updated to reflect the move.
 */

// The main function to generate hard move.
void generateHardMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
    GamePhase phase = getGamePhase(state);
    if (phase == OPENING) {
        generateMediumMove(state, r1, c1, r2, c2);
    }
	else {
	    generateParallelMinimaxMove(state, r1, c1, r2, c2);
	}
}