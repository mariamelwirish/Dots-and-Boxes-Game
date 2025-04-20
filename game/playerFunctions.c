#include "headers.h"

void getPlayerMove(GameState *state, int *r1, int *c1, int *r2, int *c2) {
    while (1) {
        if (scanf("%d %d %d %d", r1, c1, r2, c2) != 4) {
            printf("Invalid input. Please enter four integers.\n");
			while (getchar() != '\n');
            continue;
        }
        
        // Edge Case 1: Out-of-range coordinates.
        if (*r1 < 0 || *r1 >= ROW_SIZE || *r2 < 0 || *r2 >= ROW_SIZE ||
            *c1 < 0 || *c1 >= COL_SIZE || *c2 < 0 || *c2 >= COL_SIZE) {
            printf("Coordinates out of bounds. Valid rows: 0 to %d, valid columns: 0 to %d.\n",
                   ROW_SIZE - 1, COL_SIZE - 1);
            continue;
        }
        
        // Edge Case 2: The move must be horizontal or vertical (adjacent dots).
        if (!((*r1 == *r2 && abs(*c1 - *c2) == 1) ||
              (*c1 == *c2 && abs(*r1 - *r2) == 1))) {
            printf("Invalid move: You must connect two adjacent dots horizontally or vertically.\n");
            continue;
        }
        
        // Edge Case 3: Check if the line is already drawn.
        // Pass the coordinate values to drawLine. If it returns 0, the move is invalid.
        if (drawLine(state, *r1, *c1, *r2, *c2) == 0) {
            printf("Line already drawn. Please choose a different move.\n");
            continue;
        }

        break;
    }
}

// checks if all boxes are drawn (i.e. if game is over)
int isGameOver(GameState *state) {
    return (state->no_boxes == BOXES ? 1 : 0);
}

// switch turn when needed
void switchTurn(GameState *state) {
    state->cur_player = !(state->cur_player);
}

// calculate the scores each time a line is drawn
void calculateScores(GameState *state, int r1, int c1, int r2, int c2) {
	int result = checkBox(state, r1, c1, r2, c2);
    if(result != 0) {
        state->scores[0] += (state->cur_player == 0 ? result : 0);
		state->scores[1] += (state->cur_player == 1 ? result : 0);
    }
    else {
        switchTurn(state);
    }
}

// announce the winner
void announceWinner(GameState *state) {
    if(state->scores[0] > state->scores[1]) {
        printf("Player A wins!\n");
    }
    else if(state->scores[0] < state->scores[1]) {
        printf("Player B wins!\n");
    }
    else {
        printf("It's a tie!\n");
    }
}