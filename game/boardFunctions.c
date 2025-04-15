#include "boardFunctions.h"

// helper function that will be used to determine if the line is "-" or "|"
int fixedRow(GameState *state, int r1, int c1, int r2, int c2) {
    if(r1 == r2) return 1;
    else if(c1 == c2) return 2;
    else return 0;
}

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

