/*Sean Solberg
 * CS362 Assignment 4
 * 5-10-2018
 * Test of Great Hall Card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "Great Hall"
#define NUM_TEST 100

int main() {

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, great_hall};
        int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
        int seed;
        int numPlayers;
	int failedTests = 0; int goodTests = 0;
        printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

        int i;
        for (i =0; i < NUM_TEST; i++)
        {
		//Setup
                numPlayers = (rand() % MAX_PLAYERS-1) + 2;
                srand(time(NULL));
		seed = rand();

                initializeGame(numPlayers, k, seed, &G);
                memcpy(&testG, &G, sizeof(struct gameState));
                printf("num players %d\n", numPlayers+1);
		
		//Save all players initial cards for comparison
		int deckCards[5];
                int counter;
                for(counter=0; counter<numPlayers; counter++)
                {
                        deckCards[counter] = testG.deckCount[counter];
                }

                int curPlayer;
                for (curPlayer = 0; curPlayer < numPlayers; curPlayer++)
                {
			//Assign random values to deck and hand
			testG.handCount[curPlayer] = rand()%MAX_HAND;
                        testG.deckCount[curPlayer] = rand()%MAX_DECK;

                        int handCountBefore = testG.handCount[curPlayer];
                        int deckCountBefore = testG.deckCount[curPlayer];
                        int actionCardsBefore = testG.numActions;
                        
                        cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
                        printf("Hand count before %d and after %d\n", handCountBefore, testG.handCount[curPlayer]);
                        printf("Deck count before %d and after %d\n", deckCountBefore, testG.deckCount[curPlayer]);
                        
			//Check state of all other players cards to see if changed
			int j;
                        for(j=0; j<numPlayers; j++)
                        {
                                if(j!=curPlayer)
                                {
                                        if(G.deckCount[j] != deckCards[j])
                                                printf("error in deck counts for player %d before %d after %d\n", j, G.deckCount[j], deckCards[j]);
                                }
                        } 

			printf("Action cards before %d and after %d\n", actionCardsBefore, testG.numActions);
			
			//Final check to see if test passed
			if ((handCountBefore != testG.handCount[curPlayer]) || (deckCountBefore == testG.deckCount[curPlayer]) ||(actionCardsBefore == testG.numActions))
			{ 
				failedTests++;
				printf("FAILED TEST\n");
				printf(" NumPlayer was %d, seed was %d, iteration was %d, curPlayer was %d!\n", numPlayers, seed, i, curPlayer);
			}
			else
				goodTests++;
                        endTurn(&testG);
                }
        }
	printf("Number of tests runs: %d, number of passes: %d, number of fails: %d\n", NUM_TEST, goodTests, failedTests); 
        return 0;
}
     
