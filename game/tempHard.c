#include "tempHard.h"

int flag = 0;
char my_char = ' ', opp_char = ' ';
int my_turn = -1;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// A function to determine the game phase (opening, midgame, endgame) to determine which algorithm to play.
GamePhase getGamePhase(GameState *state) {
    int loose_boxes = 0, total_boxes = (ROW_SIZE - 1) * (COL_SIZE - 1);
    int filled_lines = 0, total_lines = (ROW_SIZE * (COL_SIZE - 1)) + ((ROW_SIZE - 1) * COL_SIZE);
    bool end_game = true;

    for (int row = 0; row < 2 * ROW_SIZE - 1; row++) {
        for (int col = 0; col < 2 * COL_SIZE - 1; col++) {
            if ((row % 2 == 0 && col % 2 == 1) || (row % 2 == 1 && col % 2 == 0)) {
                if (state->board[row][col] != ' ')
                    filled_lines++;
            }
            if (row % 2 == 1 && col % 2 == 1 && state->board[row][col] == ' ') {
                int edges = countEdges(state, row, col);
                if (edges <= 1) loose_boxes++;
                if (edges != 4 && edges != 2) end_game = false;
            }
        }
    }

    float loose_ratio = (float)loose_boxes / total_boxes;
    float progress = (float)filled_lines / total_lines;

    if (loose_ratio >= 0.2 && progress < 0.2) {
        return OPENING;
    }

    else if (end_game) {
        return ENDGAME;
    }

    else
        return MIDGAME;
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
                    eval -= 2; // avoid giving opponent a box
                } else if (edgeCount == 1) {
                    eval += 2; // potential trap
                } else if (edgeCount == 2) {
                    eval += 1; // may become chain in future
                }
            }

        }
    }
    return eval + 3 * (state->scores[my_turn] - state->scores[!my_turn]);

}

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

// Mid-game move generator using minimax
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

#define MAX_MOVES 200


typedef struct {
    GameState state;
    int r1, c1, r2, c2;
    int score;
    bool is_valid;
} MinimaxThreadData;

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

void generateParallelMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
    my_turn = state->cur_player;
    my_char = (my_turn == 0) ? 'A' : 'B';
    opp_char = (my_turn == 0) ? 'B' : 'A';
    pthread_t threads[MAX_MOVES];
    MinimaxThreadData thread_data[MAX_MOVES];
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

            if (thread_count >= MAX_MOVES) continue; // prevent overflow

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
