
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../game/driverFunctions.c"
#include "../game/boardFunctions.c"
#include "../game/playerFunctions.c"
#include "../game/botFunctions.c"

// Testing initializeGame(), which is supposed to analyze everything to 0.
void test_initializeGame() {
    GameState s;
    initializeGame(&s);
    assert(s.cur_player == 0);
    assert(s.no_boxes == 0);
    assert(s.scores[0] == 0 && s.scores[1] == 0);
    assert(s.moves == 0);
}

/*
    Testing fixedRow(), which takes coordinates and checks if the input is for horizontal or vertical line - it returns:
        0 -> if the line invalid.
        1 -> if the line is horizontal.
        2 -> if the line is vertical
 */
void test_fixedRow() {
    GameState s;
    initializeGame(&s);
    assert(fixedRow(&s, 0, 0, 0, 1) == 1);
    assert(fixedRow(&s, 0, 0, 1, 0) == 2);
    assert(fixedRow(&s, 0, 0, 1, 1) == 0);
}

/*
    Testing drawline, which takes coordinates and returns the following:
      - 1 if the line was successfully drawn using these coordinates.
      - 0 if the cell was already occupied or invalid (i.e. an error occured during drawing).
 */

void test_drawLine() {
    GameState s;
    initializeGame(&s);
    assert(drawLine(&s, 0, 0, 0, 1) == 1);
    assert(drawLine(&s, 0, 0, 0, 1) == 0);
}

/*
    Testing isBox(up/down/left/right), where each takes a line, and each returning the following:
      - 1 if there's a box completed (above/below/left to /right to) the line.
      - 0 if not.
 */
void test_isBoxHelpers() {
    GameState s;
    initializeGame(&s);
    s.cur_player = 0;
    drawLine(&s, 0, 0, 0, 1);
    drawLine(&s, 0, 0, 1, 0);
    drawLine(&s, 0, 1, 1, 1);
    drawLine(&s, 1, 0, 1, 1);
    // Boxes are actually there
    assert(isBoxDown(&s, 0, 1) == 1);
    assert(isBoxUp(&s, 2, 1) == 1);
    assert(isBoxLeft(&s, 1, 2) == 1);
    assert(isBoxRight(&s, 1, 0) == 1);
    // No Boxes there
    assert(isBoxLeft(&s, 2, 2) == 0);
}

/*
    Testing isEdge(), which takes a line and returns:
        - 1 if the line is an edge at the top of the board
        - 2 if the line is an edge at the right
        - 3 if the line is an edge is at the bottom
        - 4 if the line is an edge at the left
        - 0 if not on an edge
*/
void test_isEdge() {
    GameState s;
    initializeGame(&s);
    assert(isEdge(&s, 0, 1) == 1);
    assert(isEdge(&s, 1, 10) == 2);
    assert(isEdge(&s, 8, 1) == 3);
    assert(isEdge(&s, 1, 0) == 4);
    assert(isEdge(&s, 1, 1) == 0);
}

/*
    Testing isBox(up/down/left/right), for each returning the following:
      - 2 if the line completes 2 boxes.
      - 1 if there's a box completed (above/below/left to /right to) the line.
      - 0 if not.
 */
void test_checkBox() {
    GameState s;
    initializeGame(&s);
    s.cur_player = 0;
    drawLine(&s, 0, 0, 0, 1);
    drawLine(&s, 0, 0, 1, 0);
    drawLine(&s, 0, 1, 1, 1);
    assert(checkBox(&s, 1, 0, 1, 1) == 1);
    drawLine(&s, 1, 1, 2, 1);
    drawLine(&s, 1, 0, 2, 0);
    drawLine(&s, 2, 0, 2, 1);
    assert(checkBox(&s, 1, 0, 1, 1) == 2);
    assert(checkBox(&s, 3, 0, 3, 1) == 0);
}

// Test sswitchTurn(), which switch players turn (from A -> B and vice versa)
void test_switchTurn() {
    GameState s;
    initializeGame(&s);
    switchTurn(&s);
    assert(s.cur_player == 1);
}

// Tests isGameOver(), which checks if the game is over or not based on the number of the complete boxes, and if it's over, it returns 1.
void test_isGameOver() {
    GameState s;
    initializeGame(&s);
    assert(isGameOver(&s) == 0);
    s.no_boxes = (ROW_SIZE - 1) * (COL_SIZE - 1);
    assert(isGameOver(&s) == 1);
}

// Tests calculateScores(), which takes the coordinates of the drawn line, checks if this line completes a box or not and changes the scores[cur_player]
void test_calculateScores() {
    GameState s;
    initializeGame(&s);
    s.cur_player = 0;
    drawLine(&s, 0, 0, 0, 1);
    drawLine(&s, 0, 0, 1, 0);
    drawLine(&s, 0, 1, 1, 1);
    calculateScores(&s, 1, 0, 1, 1);
    assert(s.scores[0] == 1);
}

// Test generateEasyMove(), which takes the coordinates and generate a line randomly. It should generate a valid line (drawLine = 0)
void test_generateEasyMove() {
    GameState s;
    initializeGame(&s);
    int r1, c1, r2, c2;
    generateEasyMove(&s, &r1, &c1, &r2, &c2);
    assert(drawLine(&s, r1, c1, r2, c2) == 0);
}

// Test countEdges(), which takes a box coordinate and count the edges surrounding it and returns a number from [0-4]
void test_countEdges() {
    GameState s;
    initializeGame(&s);
    assert(countEdges(&s, 1, 1) == 0);
    drawLine(&s, 0, 0, 0, 1);
    assert(countEdges(&s, 1, 1) == 1);
    drawLine(&s, 0, 0, 1, 0);
    assert(countEdges(&s, 1, 1) == 2);
    drawLine(&s, 0, 1, 1, 1);
    assert(countEdges(&s, 1, 1) == 3);
    drawLine(&s, 1, 0, 1, 1);
    assert(countEdges(&s, 1, 1) == 4);
}

// Tests generateMediumMove(), which should generate a valid line after running.
void test_generateMediumMove() {
    GameState s;
    initializeGame(&s);
    int r1, c1, r2, c2;
    generateMediumMove(&s, &r1, &c1, &r2, &c2);
    assert(drawLine(&s, r1, c1, r2, c2) == 0);
}

/*
    Tests getGamePhase(), which returns:
        - OPENING if the game is in the first 15% of total moves.
        - MIDGAME otherwise
*/
void test_getGamePhase() {
    GameState s;
    initializeGame(&s);
    s.moves = 0;
    assert(getGamePhase(&s) == OPENING);
    s.moves = 0.3 * TOTAL_MOVES;
    assert(getGamePhase(&s) == MIDGAME);
}

// Tests evaluateBoard(), which is used in minimax to evaluate the moves.
// initially, it should return 0 since no points are rewarded for no moves.
void test_evaluateBoard() {
    GameState s;
    initializeGame(&s);
    my_turn = 0;
    my_char = 'A';
    opp_char = 'B';
    assert(evaluateBoard(&s) == 0);
}

// Tests generateHardMove(), which should generate a valid line after running.
void test_generateHardMove() {
    GameState s;
    initializeGame(&s);
    int r1, c1, r2, c2;
    generateHardMove(&s, &r1, &c1, &r2, &c2);
    assert(drawLine(&s, r1, c1, r2, c2) == 0);
}

int main() {
    test_initializeGame();
    test_fixedRow();
    test_drawLine();
    test_isBoxHelpers();
    test_isEdge();
    test_checkBox();
    test_switchTurn();
    test_isGameOver();
    test_calculateScores();
    test_generateEasyMove();
    test_countEdges();
    test_generateMediumMove();
    test_getGamePhase();
    test_evaluateBoard();
    test_generateHardMove();
    printf("All listed functions passed tests successfully!\n");
    return 0;
}
