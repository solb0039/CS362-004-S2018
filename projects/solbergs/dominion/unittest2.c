#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTFUNC "supplyCount"
//int supplyCount(int, struct gameState);

int main(){

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
        int numPlayers = 2;
        int seed = 1000;
        int testReturn;
	int test1 = 0; int test2 = 0; int test3 = 0; 

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);
        // initialize a game state and player cards
        testReturn = initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	//state->supplyCount[silver] = 40;;
	enum CARD acard = silver;
	testReturn = supplyCount(acard , &G);
	printf("\nTest 1: Testing Card: Silver\n");
	printf("Expected result 40, Test result %d\n", testReturn);
	if(testReturn == 40)
		test1 = 1;

	//state->supplyCount[estate] = 8;
	acard = estate;
	testReturn = supplyCount(acard , &G);
	printf("\nTest 2: Testing Card: Estate\n");
	printf("Expected result 8, Test result %d\n", testReturn);
	if(testReturn == 8)
		test2 = 1;

	testReturn = supplyCount(100, &G);
	printf("\nTest 3: Testing Invalid Input\n");
	printf("Expected result 0, Test result %d\n", testReturn);
	if(testReturn == 0)
		test3 = 1;

	//Test that card supply count didnt change after chaning players
	acard = copper;
	printf("\nTest 4: Test that supply doesnt change after changing players\n" );	
	printf("Before: Supply of copper cards is %d\n", supplyCount(acard, &G));
	endTurn(&G);
	printf("After: Supply of copper cards is %d\n", supplyCount(acard, &G));
	
	
	if (test1 && test2 && test3)
                printf("\nALL TESTS COMPLETED SUCCESSFULLY\n");
        else
                printf("\nOVERALL TEST FAILED\n");

	printf("\n");
	return 0;
}

       


