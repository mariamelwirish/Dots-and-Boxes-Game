#include "helpers.h"

// Returns 1 if fixed row, 2 if fixed column, 0 if no fixed
int fixedRow(int r1, int c1, int r2, int c2) {
	if(r1 == r2) return 1;
	else if(c1 == c2) return 2;
	else return 0;
}

