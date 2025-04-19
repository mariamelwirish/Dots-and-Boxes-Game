#ifndef TEMP_HARD_H
#define TEMP_HARD_H

#define DEPTH 5
#include <pthread.h>
#include <limits.h>
#include "botFunctions.h"
#include "boardFunctions.h"
#include "driverFunctions.h"
#include "playerFunctions.h"



typedef enum {OPENING, MIDGAME, ENDGAME} GamePhase;

GamePhase getGamePhase(GameState* state);
void generateSafeMove(GameState* state, int *r1, int *c1, int *r2, int *c2);
int evaluateBoard(GameState *state);
int minimax(GameState *state, int depth, bool isBot, int alpha, int beta);
void generateMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void generateParallelMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void generateParityChainMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void generateHardMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void generateHardMoveOne(GameState *state, int *r1, int *c1, int *r2, int *c2);

#endif
