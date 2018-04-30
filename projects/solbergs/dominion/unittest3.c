#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTFUNC "shuffle"


int main(){

        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
        int numPlayers = 2;
        int seed = 1000;
        int testReturn;
	int cardVal;
	int origDeck[10];
	int shufDeck[10];
	int test1 = 0; int test2 = 0; int test3 = 0; int test4 = 0;

         // initialize a game state and player cards
	testReturn = initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));	

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);
	testReturn = shuffle(1, &G);
	printf("\nTest 1: Testing good input: Return value expected = 0, Actual value = %d\n", testReturn);
	if(testReturn == 0)
		test1 = 1;	

	testReturn = shuffle(-1, &G);
	printf("\nTest 2: Testing bad input\n");
	printf("Return value expected = -1, Actual value = %d\n", testReturn);
	if(testReturn == -1)
		test2 =1;

	printf("\nTest 3: Test order of deck\n");
	printf("\nOriginal card deck was: ");
	int i;
	for (i=0; i<10; i++)
	{
		cardVal = G.deck[1][i];
		printf("%d ", cardVal);
		origDeck[i] = cardVal;
	}		
	printf("\n");
	shuffle(1, &G);
	printf("Shuffled card deck is: ");
	for(i=0; i<10; i++)
	{	
		cardVal = G.deck[1][i];
		printf("%d ", cardVal);
		shufDeck[i] = cardVal;
	}	
	printf("\n");
	
	int flag = 0;	
	int counter =0;
	do{
		if(origDeck[counter] != shufDeck[counter])
			flag = 1;
		counter++;
	} while (!flag);

	if(flag)
	{
		printf("Shuffle test passed\n");
		test3 = 1;
	}
	else 
		printf("Shuffle test failed\n");


	printf("\nTest 4: Test that other player's deck was not shuffled\n");
	printf("\nOriginal card deck was: ");
	for (i=0; i<10; i++)
	{
		cardVal = testG.deck[0][i];
		printf("%d ", cardVal);
		origDeck[i] = cardVal;
	}		
	printf("\n");
	printf("Same deck after shuffling other player's deck is: ");
	for(i=0; i<10; i++)
	{	
		cardVal = G.deck[0][i];
		printf("%d ", cardVal);
		shufDeck[i] = cardVal;
	}	
	
	flag = 0;	
	counter =0;
	do{
		if(origDeck[counter] != shufDeck[counter])
			flag = 1;
		counter++;
	} while (!flag);

	if(flag)
	{
		printf("\nOther player shuffle test passed\n");
		test4 = 1;
	}
	else 
		printf("\nShuffle test failed\n");



	if (test1 && test2 && test3 && test4)
                printf("\nALL TESTS COMPLETED SUCCESSFULLY\n");
        else
                printf("\nOVERALL TEST FAILED\n");

	printf("\n");
	return 0;
}
