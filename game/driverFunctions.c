#include "headers.h"
/**
 * void initializeGame(GameState *state)
 *
 * Requires:
 *      - state != NULL
 *      - state points to a valid GameState struct.
 *
 * Effects:
 *      - Initializes the game board with dots (.) and empty spaces.
 *      - Sets both players' scores to 0.
 *      - Sets the number of completed boxes to 0.
 *      - Sets the current player to 0 (Player A).
 *
 * Returns:
 *      None.
 */
void initializeGame(GameState *state) {
	// Setting up the board.
	for(int row = 0; row <= 2 * (ROW_SIZE - 1); row++) {
		for(int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
			if(row % 2 == 0 && col % 2 == 0) 
				state->board[row][col] = '.';
			else if(row % 2 == 0 && col % 2 == 1)
				state->board[row][col] = ' ';
			else
				state->board[row][col] = ' ';
		}
	}

	// Setting scores to 0.
	state->scores[0] = 0;
	state->scores[1] = 0;

	// Player 1 starts.
	state->cur_player = 0;

	// Number of boxes = 0
	state->no_boxes = 0;

	// Initialize moves.
	state->moves = 0;
}


/**
 * void twoPlayer(GameState *state)
 *
 * Requires:
 *      - state != NULL
 *      - state is properly initialized using initializeGame.
 *
 * Effects:
 *      - Runs the main game loop for two human players until the game ends.
 *      - Repeatedly displays the board, prompts for player input, validates moves,
 *        calculates scores, and switches turns.
 *      - Updates the GameState after each move.
 *
 * Returns:
 *      None.
 */
// the main function to run the game - called in main.c
void twoPlayer(GameState *state) {
	
	do { 
		displayBoard(state);
		printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", (state->cur_player == 0 ? 'A' : 'B'));
		int r1, c1, r2, c2;
		getPlayerMove(state, &r1, &c1, &r2, &c2);
		calculateScores(state, r1, c1, r2, c2);
		printf("******************************************************************************\n");
		printf("Player A score: %d\n", state->scores[0]);
		printf("Player B score: %d\n", state->scores[1]);
		printf("******************************************************************************\n");
	} while (!isGameOver(state));
	
}
/**
 * void bot(GameState *state, int mode)
 *
 * Requires:
 *      - state != NULL
 *      - state is properly initialized using initializeGame.
 *      - mode belongs to  {1, 2, 3}, where:
 *            1 → Easy Bot
 *            2 → Medium Bot
 *            3 → Hard Bot
 *
 * Effects:
 *      - Runs the game loop between a human player (Player A) and a bot (Player B) until the game ends.
 *      - Prompts the user for input on their turn, and lets the bot make a move on its turn.
 *      - Selects bot behavior based on the mode.
 *      - Updates the GameState after each move and prints score updates.
 *
 * Returns:
 *      None.
 */
void bot(GameState *state, int mode) {
    while (!isGameOver(state)) {
    	(state->moves)++;
        int r1, c1, r2, c2;
        if (state->cur_player == 0) {    // cur player = 0 means the player is a human
            // Human turn: display board and prompt for input.
            displayBoard(state);
            printf("Player A's turn. Enter your move (row1 col1 row2 col2): ");
            
            getPlayerMove(state, &r1, &c1, &r2, &c2);
           
        } else {
            // Bot turn: do not display the board; instead, show bot's chosen move.
			if(mode == 1)
            	generateEasyMove(state, &r1, &c1, &r2, &c2);
			else if(mode == 2)
				generateMediumMove(state, &r1, &c1, &r2, &c2);
			else if(mode == 3)
				generateHardMove(state, &r1, &c1, &r2, &c2);
            printf("Bot chose move: (%d, %d) to (%d, %d)\n", r1, c1, r2, c2);
            
        }
        calculateScores(state, r1, c1, r2, c2);
		printf("******************************************************************************\n");
		printf("Player A score: %d\n", state->scores[0]);
		printf("Player B score: %d\n", state->scores[1]);
		printf("******************************************************************************\n");
    }
}
