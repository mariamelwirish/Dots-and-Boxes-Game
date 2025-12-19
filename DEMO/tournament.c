#include <stdio.h>
#include <stdlib.h>
#include "../game/driverFunctions.c"
#include "../game/boardFunctions.c"
#include "../game/playerFunctions.c"
#include "../game/botFunctions.c"

void selectPlayer(GameState *state, int choice) {
    int mode = (choice == 1 ? 0 : 1);
    while (!isGameOver(state)) {
        (state->moves)++;
        int r1, c1, r2, c2;
        if (state->cur_player == mode) {
            printf("Bot's turn...\n");
             generateHardMove(state, &r1, &c1, &r2, &c2);
            printf("Bot chose move: (%d, %d) to (%d, %d)\n", r1, c1, r2, c2);
        } else {
            printf("Human's turn...\n");
            getPlayerMove(state, &r1, &c1, &r2, &c2);
            printf("Human chose move: (%d, %d) to (%d, %d)\n", r1, c1, r2, c2);
        }
        calculateScores(state, r1, c1, r2, c2);
        displayBoard(state);
        printf("******************************************************************************\n");
        printf("Bot score: %d\n", state->scores[mode]);
        printf("Player score: %d\n", state->scores[!mode]);
        printf("******************************************************************************\n");
    }
}


int main() {
    int choice = -1;
    printf("Select the game mode:\n");
    printf("1. Bot vs Human\n");
    printf("2. Human vs Bot\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    GameState *state = (GameState *) malloc(sizeof(GameState));
    initializeGame(state);
    srand((unsigned int) time(NULL));
    printf("******************************************************************************\n");
    selectPlayer(state, choice);
    displayBoard(state);
    announceWinner(state);

    return 0;
}
