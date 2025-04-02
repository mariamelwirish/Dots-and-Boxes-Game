#ifndef BOT_FUNCTIONS_H
#define BOT_FUNCTIONS_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "boardFunctions.h"

void generateEasyMove(int *r1, int *c1, int *r2, int *c2);
void drawRandomEdge(int *row, int *col);
int countEdges(int *row, int *col);
void generateMediumMove(int *r1, int *c1, int *r2, int *c2);

#endif