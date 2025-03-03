#include <stdio.h>

void displayBoard(int gridSize, int board[][2 * gridSize - 1]) {
    int row, col;

    for (row = 0; row < 2 * gridSize - 1; row++) {
        for (col = 0; col < 2 * gridSize - 1; col++) {
            if (row % 2 == 0 && col % 2 == 0) {
                printf("• "); 
            } else if (row % 2 == 0 && col % 2 == 1) {
                if (board[row][col] == 1) {
                    printf("─ ");
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
                    printf("%c ", board[row][col]); 
                }
            }
        }
        printf("\n");
    }
}

int main() {
    int gridSize = 4;
    int board[7][7] = {0}; 

    board[0][1] = 1; 
    board[1][0] = 1; 
    board[1][2] = 'A'; 

    displayBoard(gridSize, board);
    return 0;
}
