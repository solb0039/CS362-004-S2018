#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Great Hall"

int main() {

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, great_hall};
        int numPlayers = 2;
        int seed = 1000;
        int choice1 = 0; int choice2 = 0; int choice3 = 3; int handpos = 0; int bonus = 0;
        int testReturn;
        int actionsGained = 1;
	int test1 = 0; int test2 = 0; int test3 = 0; int test4 = 0;	

	/* initialize a game state and player cards*/
        initializeGame(numPlayers, k, seed, &G);
        
        printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	memcpy(&testG, &G, sizeof(struct gameState));

        printf("Test 1: Test function return.\n");
        testReturn = cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

        if(testReturn == 0)
        {
		printf("Test succeeded\n");
		test1 = 1;
	}
	 else
                printf("Test failed\n");

        printf("\nTest 2: Test that action was gained.\n");        
        int numActions = testG.numActions;
        printf("Expected number of actions: %d, actual number of actions: %d\n", G.numActions + actionsGained , numActions );

        if(G.numActions + actionsGained == numActions)
	{
                printf("Test succeeded\n");
		test2 = 1;
	}
        else
                printf("Test failed\n");	

	int player = whoseTurn(&G);
	printf("\nTest 3: Test that deck changed for player 1 and not for player 2\n");
	printf("Player %d: Before %d, after %d\n",(player+1),G.deckCount[player] ,testG.deckCount[player] );
	printf("Player %d: Before %d, after %d\n",(player+2), G.deckCount[player+1], testG.deckCount[player+1]);
	if((G.deckCount[player] !=testG.deckCount[player] ) && (G.deckCount[player+1] == testG.deckCount[player+1]))
	{
		test3 = 1;
		printf("Test succeeded\n");
	}
	else
		printf("Test failed\n");

	printf("\nTest 4: Test that discard piles changed for player 1 and not for player 2\n");
	printf("Player %d: Before %d, after %d\n", (player+1), G.playedCards[player], testG.playedCards[player] );
	printf("Player %d: Before %d, after %d\n", (player+2), G.playedCards[player+1], testG.playedCards[player+1]);

        if((G.playedCards[player]!=testG.playedCards[player]) && (G.playedCards[player+1]== testG.playedCards[player+1]))
        {
                test4 = 1;
                printf("Test succeeded\n");
        }
        else
                printf("Test failed\n");

	if (test1 && test2 && test3 && test4)
		printf("\nALL TESTS COMPLETED SUCCESSFULLY\n");
	else
		printf("\nOVERALL TEST FAILED\n");

	printf("\n");
	return 0;      
}

//int playGreatHall(int currentPlayer, struct gameState *state, int handPos)
//{
     //+1 Card
     //      drawCard(currentPlayer, state);
     //
     //            //+1 Actions
     //                  state->numActions = state->numActions +1;
     //
     //                        //discard card from hand
     //                              discardCard(handPos, currentPlayer, state, 0);
     //                                    return 0;
     //                                    }
