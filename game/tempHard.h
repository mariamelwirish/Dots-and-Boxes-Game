#ifndef TEMP_HARD_H
#define TEMP_HARD_H

#include "botFunctions.h"
#include "boardFunctions.h"
#include "driverFunctions.h"

int boxes[] = {20, 0, 0, 0};
typedef enum {OPENING, MIDGAME, ENDGAME} GamePhase;
//GamePhase getGamePhase(void);
GamePhase getGamePhase(GameState *state);
void generateSafeMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
int evaluateBoard(void);
int minimax(int depth, int alpha, int beta, int player);
void generateMinimaxMove(int *r1, int *c1, int *r2, int *c2);
void generateParityChainMove(int *r1, int *c1, int *r2, int *c2);
void generateHardMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
#endif