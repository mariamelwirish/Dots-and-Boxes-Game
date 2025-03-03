#include <stdio.h>

#define ROWS 4
#define COLS 5

void displayBoard(int grid[ROWS][COLS]) {
    printf("  ");
    for (int c = 0; c <= COLS; c++) { 
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r <= ROWS; r++) {
        printf("%d ", r); 
        for (int c = 0; c <= COLS; c++) {
            printf("."); 

            if (c < COLS && grid[r][c] == 1 && grid[r][c + 1] == 1) {
                printf("-"); 
            } else {
                printf(" "); 
            }
        }
        printf("\n");

        if (r < ROWS) {
            printf("  "); 
            for (int c = 0; c <= COLS; c++) {
                if (grid[r][c] == 1 && grid[r + 1][c] == 1) {
                    printf("| "); 
                } else {
                    printf("  "); 
                }
            }
            printf("\n");
        }
    }
}

int main() {
    int grid[ROWS][COLS] = {0}; 

    
    grid[0][4] = 1;
    grid[0][3] = 1;

    displayBoard(grid);

    return 0;
}
