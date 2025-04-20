#ifndef HEADERS_H
#define HEADERS_H

#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define	ROW_SIZE 4
#define COL_SIZE 5
#define BOXES ((ROW_SIZE - 1)* (COL_SIZE - 1))
#define DEPTH 6
#define THREADS 200
#define TOTAL_MOVES (((ROW_SIZE - 1) * (COL_SIZE)) + (ROW_SIZE * (COL_SIZE - 1)))

typedef enum {OPENING, MIDGAME} GamePhase;
typedef struct {
    int scores[2];
    int no_boxes;
    int cur_player;
    char board[2 * ROW_SIZE - 1][2 * COL_SIZE - 1];
    int moves;
} GameState;



// Driver Functions
void initializeGame(GameState *state);
void twoPlayer(GameState *state);
void bot(GameState *state, int mode);

// BoardFunctions
int fixedRow(GameState*state, int r1, int c1, int r2, int c2);
int drawLine(GameState *state, int r1, int c1, int r2, int c2);
void displayBoard(GameState *state);
int isBoxRight(GameState *state, int row, int col);
int isBoxLeft(GameState *state, int row, int col);
int isBoxUp(GameState *state, int row, int col);
int isBoxDown(GameState *state, int row, int col);
int isEdge(GameState* state, int row, int col);
int checkBox(GameState *state, int r1, int c1, int r2, int c2);

// Bot Functions
void generateEasyMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void drawRandomLine(GameState *state, int *r1, int *c1, int *r2, int *c2, int row, int col);
int countEdges(GameState *state, int row, int col);
void generateMediumMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
GamePhase getGamePhase(GameState* state);
void generateSafeMove(GameState* state, int *r1, int *c1, int *r2, int *c2);
int evaluateBoard(GameState *state);
int minimax(GameState *state, int depth, bool isBot, int alpha, int beta);
void generateMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void generateParallelMinimaxMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
void generateHardMove(GameState *state, int *r1, int *c1, int *r2, int *c2);

// Player Functions
void getPlayerMove(GameState *state, int *r1, int *c1, int *r2, int *c2);
int isGameOver(GameState* state);
void switchTurn(GameState* state);
void calculateScores(GameState* state, int r1, int c1, int r2, int c2);
void announceWinner(GameState *state);

#endif