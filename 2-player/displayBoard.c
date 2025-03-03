#include <stdio.h>
#include "initializeGame.h"

void displayBoard(int board[ROW_SIZE][COL_SIZE]) {
    printf("  ");
    for (int col = 0; col <= COL_SIZE; col++) { 
        printf("%d ", col);
    }
    printf("\n");

    for (int row = 0; row <= ROW_SIZE; row++) {
        printf("%d ", row); 
        for (int col = 0; col <= COL_SIZE; col++) {
            printf("."); 

            if (col < COL_SIZE && board[row][col] == 1 && board[row][col + 1] == 1) {
                printf("-"); 
            } else {
                printf(" "); 
            }
        }
        printf("\n");

        if (row < ROW_SIZE) {
            printf("  "); 
            for (int col = 0; col <= COL_SIZE; col++) {
                if (board[row][col] == 1 && board[row + 1][col] == 1) {
                    printf("| "); 
                } else {
                    printf("  "); 
                }
            }
            printf("\n");
        }
    }
}
