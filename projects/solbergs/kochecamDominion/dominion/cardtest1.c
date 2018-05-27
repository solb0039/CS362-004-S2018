
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"

int main() {

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;int numPlayers = 2;	
	int smithyCardsDraw = 3;
	int numCardDiscard = 1;
	int testReturn;
	int test1 = 0; int test2 = 0; int test3 = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	memcpy(&testG, &G, sizeof(struct gameState));

	testReturn = cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	int player = whoseTurn(&testG);

	printf("Test 1: Test fuction return with valid input\n");
	printf("Expected 0 Actual %d \n", testReturn);
        if(testReturn == 0)
        {
	        printf("Test succeeded\n");
        	test1 = 1;
	}
	else
        
	        printf("Test failed\n");
	
	printf("\nTest 2: Test valid input --> Number of cards drawn\n");
	//numnber of cards drawn should be 3
	int postCount = testG.handCount[player];
	printf("Expected %d Actual %d \n", G.handCount[player] + smithyCardsDraw-numCardDiscard, postCount);

	if((G.handCount[player] + smithyCardsDraw-numCardDiscard) !=  postCount)
		printf("Test failed\n");
	else
	{
		printf("Test succeeded\n");
		test2 = 1;
	}

	//Test that cards came from own deck and other players ahnd didnt change
	printf("\nTest 3: Test that cards came from current player's deck and not other players deck\n");	
	printf("Player %d deck count: Expected %d Actual %d \n", player+1, G.deckCount[player], testG.deckCount[player]); 	
	player++;
	printf("Player %d deck count: Expected %d Actual %d \n", player+1, G.deckCount[player], testG.deckCount[player]); 	
	if((G.deckCount[player] == testG.deckCount[player]) && (G.deckCount[player-1] != testG.deckCount[player-1] ) )
	{
		test3 = 1;
		printf("Test succeeded\n");
	}
	else
		printf("Test failed\n");

	/*Check that victory and kingdom card piles did not change*/
	printf("\nTest 4: Test that victory and kingdom card piles did not change\n");
	printf("Estate cards: expected %d, actual %d \n", G.supplyCount[estate], testG.supplyCount[estate]);	
	printf("Duchy cards: expected %d, actual %d \n", G.supplyCount[duchy], testG.supplyCount[duchy]);
	printf("Province cards: expected %d, actual %d \n", G.supplyCount[province], testG.supplyCount[province]);
	printf("Copper cards: expected %d, actual %d \n", G.supplyCount[copper], testG.supplyCount[copper]);
        printf("Silver cards: expected %d, actual %d \n", G.supplyCount[silver], testG.supplyCount[silver]);
        printf("Gold cards: expected %d, actual %d \n", G.supplyCount[gold], testG.supplyCount[gold]);	

	if (test1 && test2 &&test3)
                printf("\nALL TESTS COMPLETED SUCCESSFULLY\n");
        else
                printf("\nOVERALL TEST FAILED\n");

	printf("\n");
	return 0;
}

// int caseSmithy(struct gameState *state, int handPos, int currentPlayer  )
//state->hand[player][count]
//   state->handCount[currentPlayer]--;
