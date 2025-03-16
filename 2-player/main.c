#include "boardFunctions.c"
#include "playerFunctions.c"
#include "driverFunctions.c"
#include "botFunctions.c"

// main function calls playGame
int main() {
	srand((unsigned int) time(NULL)); 
	// Ask user to select mode and handle it.
	int choice;
	while (true) {
		printf("Select game mode:\n");
		printf("1. Play against another player\n");
		printf("2. Play against a bot\n");
		printf("Enter your choice (1 or 2): ");

		if (scanf("%d", &choice) == 1 && (choice == 1 || choice == 2)) {
			break;
		}

		printf("Invalid input. Please enter 1 or 2.\n");
		while (getchar() != '\n');
	}
	if (choice == 1) {
		twoPlayer();
	} else {
		easyMode();
	}
	displayBoard();
	announceWinner();
}