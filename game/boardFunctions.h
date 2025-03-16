#ifndef BOARD_FUNCTIONS_H
#define BOARD_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "driverFunctions.h"

int fixedRow(int r1, int c1, int r2, int c2);
int drawLine(int r1, int c1, int r2, int c2);
void displayBoard();
int isBoxRight(int row, int col);
int isBoxLeft(int row, int col);
int isBoxUp(int row, int col); 
int isBoxDown(int row, int col);
int isEdge(int row, int col);
int checkBox(int r1, int c1, int r2, int c2);

#endif