#include <stdio.h>
#include <stdlib.h>
#include "../game/driverFunctions.c"
#include "../game/boardFunctions.c"
#include "../game/playerFunctions.c"
#include "../game/botFunctions.c"

// Testing Easy Bots Against Eachother
void easyBots() {
    GameState *state = (GameState *) malloc(sizeof(GameState));
    initializeGame(state);
    srand((unsigned int) time(NULL));
    printf("******************************************************************************\n");
    testBots(state, 1, 1);
    displayBoard(state);
    announceWinner(state);
}

// Testing Medium Bots Against Eachother
void mediumBots() {
    GameState *state = (GameState *) malloc(sizeof(GameState));
    initializeGame(state);
    srand((unsigned int) time(NULL));
    printf("******************************************************************************\n");
    testBots(state, 2, 2);
    displayBoard(state);
    announceWinner(state);
}

// Testing Hard Bots Against Eachother
void hardBots() {
    GameState *state = (GameState *) malloc(sizeof(GameState));
    initializeGame(state);
    srand((unsigned int) time(NULL));
    printf("******************************************************************************\n");
    testBots(state, 3, 3);
    displayBoard(state);
    announceWinner(state);
}

int main() {
    int choice;

    printf("Select the bot match you want to test:\n");
    printf("1. Easy vs Easy\n");
    printf("2. Medium vs Medium\n");
    printf("3. Hard vs Hard\n");
    printf("4. Custom Match (choose bot mode for each player)\n");
    printf("Enter your choice (1, 2, 3, or 4): ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    switch (choice) {
        case 1:
            easyBots();
        break;
        case 2:
            mediumBots();
        break;
        case 3:
            hardBots();
        break;
        case 4: {
            int bot1, bot2;
            printf("Choose mode for Bot A (1: Easy, 2: Medium, 3: Hard): ");
            if (scanf("%d", &bot1) != 1 || bot1 < 1 || bot1 > 3) {
                printf("Invalid input for Bot A. Exiting.\n");
                return 1;
            }
            printf("Choose mode for Bot B (1: Easy, 2: Medium, 3: Hard): ");
            if (scanf("%d", &bot2) != 1 || bot2 < 1 || bot2 > 3) {
                printf("Invalid input for Bot B. Exiting.\n");
                return 1;
            }

            GameState *state = (GameState *) malloc(sizeof(GameState));
            initializeGame(state);
            srand((unsigned int) time(NULL));
            printf("******************************************************************************\n");
            testBots(state, bot1, bot2);
            displayBoard(state);
            announceWinner(state);
            break;
        }
        default:
            printf("Invalid choice. Please run the program again and choose 1–4.\n");
        break;
    }

    return 0;
}
