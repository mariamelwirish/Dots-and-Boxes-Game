#ifndef BOT_FUNCTIONS_H
#define BOT_FUNCTIONS_H
#include "driverFunctions.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "boardFunctions.h"

void generateEasyMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void drawRandomLine(GameState *state, int *r1, int *c1, int *r2, int *c2, int row, int col);
int countEdges(GameState *state, int row, int col);
void generateMediumMove(GameState *state, int *r1, int *c1, int *r2, int *c2);

#endif