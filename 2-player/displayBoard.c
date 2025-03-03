#include <stdio.h>

#define	ROW_SIZE 5
#define COL_SIZE 6

void displayBoard(int board[2 * ROW_SIZE - 1][2 * COL_SIZE - 1]) {
    int row, col;
    for (row = 0; row <= 2 * ROW_SIZE - 1; row++) {
        for (col = 0; col < 2 * COL_SIZE - 1; col++) {
            if (row % 2 == 0 && col % 2 == 0) {
                printf(". "); 
            } else if (row % 2 == 0 && col % 2 == 1) {
                if (board[row][col] == 1) {
                    printf("- ");
                } else {
                    printf("  "); 
                }
            } else if (row % 2 == 1 && col % 2 == 0) {
                if (board[row][col] == 1) {
                    printf("| "); 
                } else {
                    printf("  "); 
                }
            } else {
                if (board[row][col] == 0) {
                    printf("  "); 
                } else {
                    printf("%c ", (char) board[row][col]); 
                }
            }
        }
        printf("\n");
    }
}

int main() {
    int board[2 * ROW_SIZE - 1][2 * COL_SIZE - 1] = {0}; 

    board[0][4] = 1; 
    board[1][4] = 1; 

    displayBoard(board);
    return 0;
}