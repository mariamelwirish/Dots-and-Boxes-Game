#ifndef PLAYER_FUNCTIONS_H
#define PLAYER_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "boardFunctions.h"

void getPlayerMove(int *r1, int *c1, int *r2, int *c2);
int isGameOver();
void switchTurn();
void calculateScores(int r1, int c1, int r2, int c2);

#endif