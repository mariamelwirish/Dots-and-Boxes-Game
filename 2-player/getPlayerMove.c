#include "initializeGame.h"  /// needed for sizes and the board
#include "helpers.c"         //// needed for the fixed 
#include "drawLine.c"
#include <stdio.h>
#include <stdlib.h>
///#include "helper.h" 
// Edge Case 1: Out of range

	// Edge Case 2: Not fixed row / col
	// Personal: fixedRow(...) == 0

	// Edge Case 3: Line already drawm
	// Personal: drawLIne(...) == 0
	

int getPlayerMove(int *r1, int *c1, int *r2, int *c2) {
    while (1) {
        
        printf("Enter your move (row1 col1 row2 col2): ");
        if (scanf("%d %d %d %d", r1, c1, r2, c2) != 4) {
            printf("Invalid input. Please enter four integers.\n");
            while (getchar() != '\n');  // Clears the input buffer.| was told that it is needed 
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
        if (drawLine(*r1, *c1, *r2, *c2) == 0) {
            printf("Line already drawn. Please choose a different move.\n");
            continue;
        }
        
       
        break;
    }
    return 1;  //  successful move.
}
