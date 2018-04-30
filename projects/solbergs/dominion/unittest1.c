
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTFUNC  "getCost"

int getCost(int);

int main(){

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	int numPlayers = 2;
	int seed = 1000;
	int testReturn;
	int test2 = 0; int test3 = 0; int test4 = 0;

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);
	// initialize a game state and player cards
	testReturn = initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("\nTest 1: Test valid input\n");
	//Test all  cards
	int costs[] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	//testReturn = getCost(7);
	printf("\nTesting Cards\n");
	
	int i;
	int flag = 0;
	for (i=0; i<27; i++)
	{
		testReturn = getCost(i);
		printf("Test result = %d, Expected value = %d\n", testReturn, costs[i]);
		if(testReturn != costs[i])
			flag = 1;
	}
	if (flag == 0) test2 = 1;
	if(test2==1)
		printf("Test succeeded\n");
	else
		printf("Test failed\n");

	//Test invalid input
	testReturn = getCost(-1);
	printf("\nTest 2: Test invalid input\n");
	printf("Test result = %d, Expected value = -1\n", testReturn);
	if(testReturn == -1)
	{
		printf("Test succeeded\n");
		test3 = 1;
	}
	else
		printf("Test failed\n");

	//Test that player cards did not change 
	printf("\nTest 3: Test that number of cards did not change\n");
	int player = whoseTurn(&G);
	printf("Player %d: Number of cards before %d, number of cards after %d\n", player+1, G.handCount[player], testG.handCount[player]);
	printf("Player %d: Number of cards before %d, number of cards after %d\n", player+2, G.handCount[player+1], testG.handCount[player+1]);
	if((G.handCount[player]== testG.handCount[player]) && (G.handCount[player+1]== testG.handCount[player+1]) )
	{
		test4 = 1;
		printf("Test succeeded\n");
	}
	else
		printf("Test failed\n");

	if (test2 && test3 && test4)
                printf("\nALL TESTS COMPLETED SUCCESSFULLY\n");
        else
                printf("\nOVERALL TEST FAILED\n");

	printf("\n");
	return 0;
}

