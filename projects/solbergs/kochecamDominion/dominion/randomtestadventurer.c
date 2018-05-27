/*Sean Solberg
 * CS362 Assignment 4
 * 5-10-2018*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "Adventurer"
#define NUM_TEST 1000

int main() {

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
        int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
        int seed;
        int numPlayers;
	int failedTests = 0;
	int totalTests = 0;

       printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

        int i;
        for (i =0; i < NUM_TEST; i++)
        {
                //Random players and seed condition     
                numPlayers = (rand() % MAX_PLAYERS-1) + 2;
                srand(time(NULL));
		seed = rand();
               
                // initialize a game state and player cards
                initializeGame(numPlayers, k, seed, &G);
                memcpy(&testG, &G, sizeof(struct gameState));
                printf("num players %d\n", numPlayers+1);
	
		//Save the initial cards into an array                
		int deckCards[5];
			int counter;
			for(counter=0; counter < numPlayers; counter++)
			{
				deckCards[counter] = testG.deckCount[counter];
			}

		//For each player, set deck count, hand count
                int curPlayer;      
  		for (curPlayer = 0; curPlayer < numPlayers; curPlayer++)
		{
			printf("Player %d\n", curPlayer+1);
			totalTests++;

			//Add possibility of empty deck to test other code in adventurer
			int chance = rand()%4;
			if(chance == 3)
			{
			        testG.handCount[curPlayer] = rand()%MAX_HAND;
                                testG.deckCount[curPlayer] = 0;
			}
			else
			{
				testG.handCount[curPlayer] = rand()%MAX_HAND;
                        	testG.deckCount[curPlayer] = rand()%MAX_DECK;		
			}

			//Save card states for comparison after playing card
			int handCountBefore = testG.handCount[curPlayer];
			int deckCountBefore = testG.deckCount[curPlayer];
			int treasureCardsBefore = 0;
			int j;
			for (j=0; j<testG.handCount[curPlayer]; j++)
			{
				if ((testG.hand[curPlayer][j] == copper) || (testG.hand[curPlayer][j]== silver) || (testG.hand[curPlayer][j] == gold)){ treasureCardsBefore++;}
			} 

			cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
			
			printf("Hand count before %d and after %d\n", handCountBefore, testG.handCount[curPlayer]);
			printf("Deck count before %d and after %d\n", deckCountBefore, testG.deckCount[curPlayer]);
		        
			//Verify that deck counts for other players did not change
                        for(j=0; j<numPlayers; j++)
                        {
                                if(j!=curPlayer)
                                {
                                        if(G.deckCount[j] != deckCards[j])
                                                printf("error in deck counts for player %d before %d after %d\n", j, G.deckCount[j], deckCards[j]);
                                }
                        }	
			
			int treasureCardsAfter = 0;
                        for (j=0; j<testG.handCount[curPlayer]; j++)
                        {
                                if ((testG.hand[curPlayer][j] == copper) || (testG.hand[curPlayer][j]== silver) || (testG.hand[curPlayer][j] == gold)){ treasureCardsAfter++;} 
                        }
			printf("Treasure count before %d and after %d\n", treasureCardsBefore, treasureCardsAfter);
				
			int drawnTreasCards = (treasureCardsAfter - treasureCardsBefore);
			printf("Number of treasure cards drawn was %d\n", drawnTreasCards );

			//Final check to see if test passed
			if((drawnTreasCards > 1) || (handCountBefore == testG.handCount[curPlayer]) || (deckCountBefore== testG.deckCount[curPlayer])|| (treasureCardsBefore==treasureCardsAfter))
			{
				if(deckCountBefore != 0)	//Cases where deck was assigned as 0
				{
					printf("Failed test\n");
					failedTests++;
				}
			}
			
			endTurn(&testG);	
		}  
	}
	printf("Total tests: %d, Total failed tests: %d\n", totalTests, failedTests);

	return 0;
}
