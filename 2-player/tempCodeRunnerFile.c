
		if(cur_player == 0)
			getPlayerMove(&r1, &c1, &r2, &c2);
		else 
			generateMove(&r1, &c1, &r2, &c2);
		calculateScores(r1, c1, r2, c2);
		printf("******************************************************************************\n");
		printf("Player A score: %d\n", score_a);
		printf("Player B score: %d\n", score_b);
		printf("******************************************************************************\n");
	} while (!isGameOver());
}