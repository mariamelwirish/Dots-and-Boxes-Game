#include "boardFunctions.c"
#include "playerFunctions.c"
#include "driverFunctions.c"
#include "botFunctions.c"

// main function calls playGame
int main() {
	srand((unsigned int) time(NULL)); 
	// Ask user to select mode and handle it.
	displayBoard();
}