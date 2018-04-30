
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"

int main() {

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
        int testReturn;
	int bonus =0;
	int choice1 =1; int choice2 = 0; int choice3 = 0;
	int seed = 1000;
	int handpos = 0;		
	int numPlayers = 2;
	int minDrawTreas = 2;
	int test1 = 0; int test2 = 0; int test3 = 0; int test4 = 0; int test5 = 0;

	/* initialize a game state and player cards*/
        initializeGame(numPlayers, k, seed, &G);
       
        printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	 memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("Test 1: Test function return.\n");
       	testReturn = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);        
	//testG.hand[0][0] = adventurer;
	//testReturn = playCard(0, choice1, choice2, choice3, &G);
	
	if(testReturn == 0)
	{
		printf("Test succeeded\n");
		test1 = 1;
	}
	else
		printf("Test failed\n");

	printf("\nTest 2: Test number of drawn treasure cards.\n");
	
	printf("Minimum number is %d, Actual was %d\n", minDrawTreas, (G.deckCount[whoseTurn(&G)] - testG.deckCount[whoseTurn(&testG)]));
	if ((G.deckCount[whoseTurn(&G)] - testG.deckCount[whoseTurn(&testG)]) < minDrawTreas )
	{
		printf("Test failed\n");
	}
	else 
	{
		printf("Test succeeded\n");
 		test2 = 1;
	}

	//Test that overall deck only changed by 1
	printf("\nTest 3: Test that decks did not change.\n");
	int player = whoseTurn(&G);
	printf("Player %d deck count: Before %d, after %d\n", (player+1),  G.deckCount[player], testG.deckCount[player]);
	//Test that other players hand wasnt changed
	printf("Player %d deck count: Before %d, after %d\n", (player+2), G.deckCount[player+1], testG.deckCount[player+1]);	
	if((G.deckCount[player] != testG.deckCount[player]) && (G.deckCount[player+1] == testG.deckCount[player+1]) )
	{
		test3 = 1;
		printf("Test succeeded\n");
	}
	else
		printf("Test failed\n");

	//Test that player hand count changed
	printf("\nTest 4: Test that player hand count changed and other players hand count did not.\n");
	printf("Player %d: Original count: %d, new count %d\n", (player+1), G.handCount[player], testG.handCount[player]);
	printf("Player %d: Original count: %d, new count %d\n", (player+2), G.handCount[player+1], testG.handCount[player+1]);
	if((G.handCount[player] = testG.handCount[player]+1) && (G.handCount[player+1] == testG.handCount[player+1]) ) 
	{
		printf("Test succeeded\n");
		test4 = 1;
	}
	else
		printf("Test failed.");


	//Test that discard pile  changed
	printf("\nTest 5: Cheack discard pile changes.\n");
	printf("Player %d: Before %d, after %d\n", (player+1), testG.discardCount[player], G.discardCount[player]);
	printf("Player %d: Before %d, after %d\n", (player+2), testG.discardCount[player+1], G.discardCount[player+1]);
	if((testG.discardCount[player] != G.discardCount[player]) && (testG.discardCount[player+1] == G.discardCount[player+1]))
	{
		test5 = 1;
		printf("Test succeeded\n");
	}
	else 
		printf("Test failed\n");

        /*Check that victory and kingdom card piles did not change*/
        printf("\nTest 6: Test that victory and kingdom card piles did not change\n");
        printf("Estate cards: expected %d, actual %d \n", G.supplyCount[estate], testG.supplyCount[estate]);    
        printf("Duchy cards: expected %d, actual %d \n", G.supplyCount[duchy], testG.supplyCount[duchy]);
        printf("Province cards: expected %d, actual %d \n", G.supplyCount[province], testG.supplyCount[province]);
        printf("Copper cards: expected %d, actual %d \n", G.supplyCount[copper], testG.supplyCount[copper]);
        printf("Silver cards: expected %d, actual %d \n", G.supplyCount[silver], testG.supplyCount[silver]);
        printf("Gold cards: expected %d, actual %d \n", G.supplyCount[gold], testG.supplyCount[gold]);  
	printf("Curse cards: expected %d, actual %d \n", G.supplyCount[curse], testG.supplyCount[curse]);


	if (test1 && test2 && test3 && test4 && test5)  
                printf("\nALL TESTS COMPLETED SUCCESSFULLY\n");
        else
                printf("\nOVERALL TEST FAILED\n");


	printf("\n");
	return 0;
	        
}

/*
int caseAdventurer(int temphand[], int drawntreasure, struct gameState *state, int currentPlayer)
{
        int cardDrawn;
        int z=0;

        while(drawntreasure<2){
        if (state->deckCount[currentPlayer] < 1){//if the deck is empty we need to shuffle discard and add to deck
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);

        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.

        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)

           drawntreasure = drawntreasure + 2;                   //BUG:  increment treasure by +2
        else{
          temphand[z]=cardDrawn;
          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
          z++;
        }
      }
      while(z-1>=0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
      }

     return 0;
}
*/
