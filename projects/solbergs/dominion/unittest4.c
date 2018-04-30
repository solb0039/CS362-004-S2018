#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTFUNC "endTurn"

//Testing of endTurn function

int main(){

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
        int numPlayers = 2;
        int seed = 1000;
        int testReturn;
	int count;
	int count2;
	int coins;
	int coins2;
	int test1 = 0; int test2 = 0; int test3 = 0; int test4 = 0; int test5 = 0; int test6 = 0;

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);
        // initialize a game state and player cards
        testReturn = initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	testReturn = whoseTurn(&G);
	count = G.handCount[testReturn];
	coins = G.coins;	

	//Change players
	endTurn(&G);

	int testReturn2 = whoseTurn(&G);
	count2 = G.handCount[testReturn];
	coins2 = G.coins;
	
	printf("Test 1: Test that player was changed.\n");
	printf("Original player: Expected 0, Actual  %d\n", testReturn);
	if(testReturn == 0)
		test1 = 1;
	printf("New player: Expected 1, Actual %d\n", testReturn2);
	if(testReturn2 == 1)
		test2 = 1;

	printf("\nTest 2: Test that player card count changed\n");
	printf("Original player 1 card count: %d\n", count);
	printf("New player 1 card count: %d\n", count2);
	if(count != count2)
		test3 =1;
	
	printf("\nTest 3: Test that player coins changed\n");
	printf("Original number of coins: %d\n", coins);
	printf("New number of coins %d\n", coins2);
	if(coins != coins2)
		test4 = 1;

	printf("\nTest 4: Call function again to see if original player is restored\n");
	testReturn = whoseTurn(&G);
	endTurn(&G);
	testReturn2 = whoseTurn(&G);
	printf("Original player: Expected 1, Actual  %d\n", testReturn);
        if(testReturn == 1)
                test5 = 1;
        printf("New player: Expected 0, Actual %d\n", testReturn2);
        if(testReturn2 == 0)
                test6 = 1;
	if (testReturn != testReturn2)
		printf("Test succeeded\n");
	else
		printf("Test failed\n");
	
	if (test1 && test2 && test3 && test4 && test5 && test6)
                printf("\nALL TESTS COMPLETED SUCCESSFULLY\n");
        else
                printf("\nOVERALL TEST FAILED\n");

	printf("\n");
        return 0;
}  






//int whoseTurn(struct gameState *state) {
 //         return state->whoseTurn;
 //       }
