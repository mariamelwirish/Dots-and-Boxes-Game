#ifndef BOARD_FUNCTIONS_H
#define BOARD_FUNCTIONS_H
#include "driverFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int fixedRow(GameState*state, int r1, int c1, int r2, int c2);
int drawLine(GameState *state, int r1, int c1, int r2, int c2);
void displayBoard(GameState *state);
int isBoxRight(GameState *state, int row, int col);
int isBoxLeft(GameState *state, int row, int col);
int isBoxUp(GameState *state, int row, int col); 
int isBoxDown(GameState *state, int row, int col);
int isEdge(GameState* state, int row, int col);
int checkBox(GameState *state, int r1, int c1, int r2, int c2);

#endif