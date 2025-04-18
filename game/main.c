#include "boardFunctions.c"
#include "playerFunctions.c"
#include "driverFunctions.c"
#include "botFunctions.c"
#include "tempHard.c"


// main function calls playGame
int main() {
	GameState *state = (GameState *) malloc(sizeof(GameState)); 
	initializeGame(state);
	srand((unsigned int) time(NULL)); 
	// Ask user to select mode and handle it.
	int choice;
	while (true) {
		printf("Select game mode:\n");
		printf("1. Play against another player.\n");
		printf("2. Play against a bot.\n");
		printf("Enter your choice (1 or 2): ");

		if (scanf("%d", &choice) == 1 && (choice == 1 || choice == 2)) {
			break;
		}

		printf("Invalid input. Please enter 1 or 2.\n");
		while (getchar() != '\n');
	}
	printf("******************************************************************************\n");
	if (choice == 1) {
		twoPlayer(state);
	} else {
		int mode;
		while(true) {
			printf("Select bot mode:\n");
			printf("1. Easy Mode.\n");
			printf("2. Medium Mode.\n");
			printf("3. Hard Mode.\n");
			printf("Enter your choice (1, 2, or 3): ");
			if (scanf("%d", &mode) == 1 && (mode == 1 || mode == 2 || mode == 3)) {
				break;
			}
			printf("Invalid input. Please enter 1 or 2.\n");
			while (getchar() != '\n');
		}
		printf("******************************************************************************\n");
		bot(state, mode);

	}
	displayBoard(state);
	announceWinner(state);
}
