#include "headers.h"



/**
 * int fixedRow(GameState *state, int r1, int c1, int r2, int c2)
 *
 * Requires:
 *      - state != NULL
 *      - The coordinates (r1, c1) and (r2, c2) must represent valid dots in the board grid.
 *
 * Effects:
 *      - Returns 1 if the line between the two points is horizontal,
 *        2 if vertical, and 0 otherwise.
 *
 * Returns:
 *      Integer: 1 (horizontal), 2 (vertical), or 0 (invalid).
 */

// helper function that will be used to determine if the line is "-" or "|"
int fixedRow(GameState *state, int r1, int c1, int r2, int c2) {
    if(r1 == r2) return 1;
    else if(c1 == c2) return 2;
    else return 0;
}


/**
 * int drawLine(GameState *state, int r1, int c1, int r2, int c2)
 *
 * Requires:
 *      - state != NULL
 *      - The coordinates form either a horizontal or vertical valid line.
 *      - The corresponding location in the board must be empty meaning line not already drawn 
 *
 * Effects:
 *      - Updates the board with a '-' for horizontal or '|' for vertical line if the cell is empty.
 *
 * Returns:
 *      - 1 if the line was successfully drawn.
 *      - 0 if the cell was already occupied or invalid.
 */

// function to draw line
int drawLine(GameState *state, int r1, int c1, int r2, int c2) {
	// draw "-"
    if(fixedRow(state, r1, c1, r2, c2) == 1) {
        int row = 2 * r1;
        int col = c1 + c2;
        if(state->board[row][col] == ' ') {
            state->board[row][col] = '-';
            return 1;
        } else {
            return 0;
        }
    } 

	// draw "|"
	else if(fixedRow(state, r1, c1, r2, c2) == 2) {
        int row = r1 + r2;
        int col = 2 * c1;
        if(state->board[row][col] == ' ') {
            state->board[row][col] = '|';
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}

/**
 * void displayBoard(GameState *state)
 *
 * Requires:
 *      - state != NULL
 *      - state->board is properly initialized with valid characters.
 *
 * Effects:
 *      - Prints the current game board (including dots, lines, and claimed boxes) to stdout.
 *
 * Returns:
 *      None.
 */
void displayBoard(GameState *state) {
	// Printing the numbers on the top (0 - 5)
	printf("  ");
	for(int num = 0; num <= 2 * (COL_SIZE - 1); num++) {
		if(num % 2 == 0)
			printf("%d", num / 2);
		else 
			printf(" ");
	}
	printf("\n");

	// Printing the grid & row numbers
	for(int row = 0; row <= 2 * (ROW_SIZE - 1); row ++) {
		// For printing the row numbers
		if(row % 2 == 0)
			printf("%d ", row / 2);
		else 
			printf("  ");

		// Printing the grid elements
		for(int col = 0; col <= 2 * (COL_SIZE - 1); col++) {
			printf("%c", state->board[row][col]);
		}
		printf("\n");
	}
}
/**
 * int isBoxRight(GameState *state, int row, int col)
 *
 * Requires:
 *      - state != NULL
 *      - The position (row, col) must be within board bounds and be part of a vertical line.
 *
 * Effects:
 *      - Checks if a completed box exists to the right of the given vertical line.
 *      - If so, increments no_boxes and labels the box with the current player's letter ('A' or 'B').
 *
 * Returns:
 *      - 1 if a box was completed to the right.
 *      - 0 otherwise.
 */

// helper function to check if there is a box on the right of the drawn line
int isBoxRight(GameState *state, int row, int col) {
	if(state->board[row - 1][col + 1] == ' ' || state->board[row + 1][col + 1] == ' ' || state->board[row][col + 2] == ' ')
		return 0;
	else {
		state->no_boxes += 1;
		state->board[row][col + 1] = (state->cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}
/**
 * int isBoxLeft(GameState *state, int row, int col)
 *
 * Requires:
 *      - state != NULL
 *      - The position (row, col) must be within board bounds and be part of a vertical line.
 *
 * Effects:
 *      - Checks if a completed box exists to the left of the given vertical line.
 *      - If so, increments no_boxes and labels the box with the current player's letter.
 *
 * Returns:
 *      - 1 if a box was completed to the left.
 *      - 0 otherwise.
 */

// helper function to check if there is a box on the left of the drawn line
int isBoxLeft(GameState *state, int row, int col) {
	if(state->board[row - 1][col - 1] == ' ' || state->board[row + 1][col - 1] == ' ' || state->board[row][col - 2] == ' ')
		return 0;
	else {
		state->no_boxes += 1;
		state->board[row][col - 1] = (state->cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}

/**
 * int isBoxUp(GameState *state, int row, int col)
 *
 * Requires:
 *      - state != NULL
 *      - (row, col) is a valid location of a horizontal edge ('-') within board bounds
 *
 * Effects:
 *      - Checks for a box above the line, and updates board and score if completed
 *
 * Returns:
 *      - 1 if a box is completed above
 *      - 0 otherwise
 */
// helper function to check if there is a box above the drawn line
int isBoxUp(GameState *state, int row, int col) {
	if(state->board[row - 1][col + 1] == ' ' || state->board[row - 1][col - 1] == ' ' || state->board[row - 2][col] == ' ')
		return 0;
	else {
		state->no_boxes += 1;
		state->board[row - 1][col] = (state->cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}
/**
 * int isBoxDown(GameState *state, int row, int col)
 *
 * Requires:
 *      - state != NULL
 *      - (row, col) is a valid location of a horizontal edge ('-') within board bounds
 *
 * Effects:
 *      - Checks for a box below the line, and updates board and score if completed
 *
 * Returns:
 *      - 1 if a box is completed below
 *      - 0 otherwise
 */
// helper function to check if there is a box below the drawn line
int isBoxDown(GameState *state, int row, int col) {
	if(state->board[row + 1][col + 1] == ' ' || state->board[row + 1][col - 1] == ' ' || state->board[row + 2][col] == ' ')
		return 0;
	else {
		state->no_boxes += 1;
		state->board[row + 1][col] = (state->cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}

/**
 * int isEdge(GameState *state, int row, int col)
 *
 * Requires:
 *      - state != NULL
 *      - (row, col) must be a valid coordinate in the board
 *
 * Effects:
 *      - Does not modify state
 *
 * Returns:
 *      - 1 if the edge is at the top of the board
 *      - 2 if the edge is at the right
 *      - 3 if the edge is at the bottom
 *      - 4 if the edge is at the left
 *      - 0 if not on an edge
 */
// This function checks if the box is at the edge of the board
int isEdge(GameState *state, int row, int col) { 
    if (row == 0) 
        return 1;
  
    else if (col == 2 * (COL_SIZE - 1))
        return 2;   

    else if (row ==  2 * (ROW_SIZE - 1))
        return 3;
   
    else if (col == 0) 
        return 4;

	else return 0;
}


/**
 * int checkBox(GameState *state, int r1, int c1, int r2, int c2)
 *
 * Requires:
 *      - state != NULL
 *      - (r1, c1) and (r2, c2) form a valid line between adjacent dots.
 *
 * Effects:
 *      - Checks if the newly drawn line completes any boxes (left, right, up, or down).
 *      - If boxes are completed, they are labeled and no_boxes is incremented accordingly.
 *
 * Returns:
 *      - 2 if two boxes are completed
 *      - 1 if one box is completed
 *      - 0 if no boxes are completed
 */
int checkBox(GameState *state, int r1, int c1, int r2, int c2) {
	// determine if it is "-" or "|"
    bool flag = (fixedRow(state, r1, c1, r2, c2) == 1 ? true : false); 
	// calculting the row and col on the board (based on if it is "-" or "|") 	
	int row = (flag ? 2 * r1 : r1 + r2);
	int col = (flag ? c1 + c2 : 2 * c1);
	int edge = isEdge(state, row, col);
	if(edge) {	// checks if it is a line is on the edge
		if (edge == 1)
			return isBoxDown(state, row, col);
		else if (edge == 2)
			return isBoxLeft(state, row, col);
		else if (edge == 3)
			return  isBoxUp(state, row, col); 
		else if (edge == 4)
			return isBoxRight(state, row, col);
   }
	else if(flag) {
		bool up = isBoxUp(state, row, col);
		bool down = isBoxDown(state, row, col);
		if(up && down) return 2;
		else return (up || down);
	}
	else {
		bool right = isBoxRight(state, row, col);
		bool left = isBoxLeft(state, row, col);
		if(right && left) return 2;
		else return (right || left);
	}
}	

