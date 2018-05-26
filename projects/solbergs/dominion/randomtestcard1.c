/*Name: Sean Solberg
 * CS362 Assignment 4
 * 5-10-2018
 * Test of Village card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "Villager"
#define NUM_TEST 100

int main() {

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
        int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
        int seed;
	int numPlayers;
	int failedTests = 0;

        printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	int i;
	for (i =0; i < NUM_TEST; i++)
	{
        	//Random players and seed condition	
		numPlayers = (rand() % MAX_PLAYERS-1) + 2;
		seed = rand();
		srand(time(NULL));

		// initialize a game state and player cards
        	initializeGame(numPlayers, k, seed, &G);
        	memcpy(&testG, &G, sizeof(struct gameState));
		printf("Number players this round: %d\n", numPlayers+1);
		
		//Save initial state of deck cards
		int deckCards[5];
		int counter;
		for(counter=0; counter<numPlayers; counter++)
		{
			deckCards[counter] = testG.deckCount[counter];
		}

		//For each player, set deck count, hand count
		int curPlayer;
		for(curPlayer = 0; curPlayer < numPlayers; curPlayer++)
		{
			testG.handCount[curPlayer] = rand()%MAX_HAND;
			testG.deckCount[curPlayer] = rand()%MAX_DECK;

			if (i == 10)
				testG.deckCount[curPlayer] = 0;
	
			//Save card states for comparison after playing card
			int handCountBefore = testG.handCount[curPlayer];
			int deckCountBefore = testG.deckCount[curPlayer];
			int playedCardCountBefore = testG.playedCardCount;
			int numActionsBefore = testG.numActions;
			
			cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
      			
			printf("Player %d\n", curPlayer);	
			//Verify that hand count increased by 1
			printf("hand count before: %d and after %d\n", handCountBefore, testG.handCount[curPlayer]);
			//Verify that deckCount decreased by 1 
			printf("deck count before: %d and after %d\n", deckCountBefore, testG.deckCount[curPlayer]);
		
	
			//Verify that other players deck count did not change
			int j;
			for(j=0; j<numPlayers; j++)
			{
				if(j!=curPlayer)
				{
					if(G.deckCount[j] != deckCards[j])
						printf("error in deck counts for player %d before %d after %d\n", j, G.deckCount[j], deckCards[j]);	
				}
			}

			//Verify that played cardcount increased by 1
			printf("Played card count before %d and after %d\n", playedCardCountBefore, testG.playedCardCount);
			//Verify that number of actions changed 
			printf("Number of actions before %d and after %d\n", numActionsBefore, testG.numActions);			     printf("discard %d\n", testG.discardCount[curPlayer]);
			
			//Final check on card to see if test passed
			if(( handCountBefore!=testG.handCount[curPlayer])||(deckCountBefore==testG.deckCount[curPlayer])||(playedCardCountBefore==testG.playedCardCount)||(numActionsBefore != testG.numActions+1))
			{
				if(deckCountBefore != 0){
				printf("Failed test\n");
				failedTests++;}
				//Extra error reporting
				if (numActionsBefore != testG.numActions+1)
					printf("Number of actions gained was not 2\n");
			}			
			endTurn(&testG);		
		}	
 
	}
	printf("Total failed tests: %d\n", failedTests);
	return 0;
}

