#include "checkBox.h"

int isBoxRight(int row, int col) {
	if(board[row - 1][col + 1] == ' ' || board[row + 1][col + 1] == ' ' || board[row][col + 2] == ' ')
		return 0;
	else {
		no_boxes += 1;
		board[row][col + 1] = (cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}

int isBoxLeft(int row, int col) {
	if(board[row - 1][col - 1] == ' ' || board[row + 1][col - 1] == ' ' || board[row][col - 2] == ' ')
		return 0;
	else {
		no_boxes += 1;
		board[row][col - 1] = (cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}

int isBoxUp(int row, int col) {
	if(board[row - 1][col + 1] == ' ' || board[row - 1][col - 1] == ' ' || board[row - 2][col] == ' ')
		return 0;
	else {
		no_boxes += 1;
		board[row - 1][col] = (cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}

int isBoxDown(int row, int col) {
	if(board[row + 1][col + 1] == ' ' || board[row + 1][col - 1] == ' ' || board[row + 2][col] == ' ')
		return 0;
	else {
		no_boxes += 1;
		board[row + 1][col] = (cur_player == 0 ? 'A' : 'B');
		return 1; 
	}
}

// This function checks if the box is at the edge of the board
int isEdge(int row, int col) { 
    if (row == 0) 
        return 1;
  
    else if (col == 2 * COL_SIZE)
        return 2;   

    else if (row ==  2 * ROW_SIZE) 
        return 3;
   
    else if (col == 0) 
        return 4;
	else return 0;
}


int checkBox(int r1, int c1, int r2, int c2) {
  
    bool flag = (fixedRow(r1, c1, r2, c2) == 1 ? true : false);  	
	int row = (flag ? 2 * r1 : r1 + r2);
	int col = (flag ? c1 + c2 : 2 * c1);
	int edge = isEdge(row, col);
	if(edge) {	// checks if it is a line is on the edge
		if (edge == 1)
			return   isBoxDown(row, col);
		else if (edge == 2)
			return isBoxLeft(row, col);
		else if (edge == 3)
			return  isBoxUp(row, col); 
		else if (edge == 4)
			return isBoxRight(row, col);
   }
	else if(flag)
		return (isBoxUp(row, col) || isBoxDown(row, col));
	else 
		return (isBoxRight(row, col) || isBoxLeft(row, col));
}	

