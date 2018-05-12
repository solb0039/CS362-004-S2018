CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest_1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

unittest_2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

unittest_3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

unittest_4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

cardtest_1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

cardtest_2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

cardtest_3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

cardtest_4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

unittestresults.out: unittest_1 unittest_2 unittest_3 unittest_4 cardtest_1 cardtest_2 cardtest_3 cardtest_4 	
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c -bf >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out	


randomtest1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o -coverage -fpic -lm -g $(CFLAGS)

randomtestresults.out: randomtest1 randomtest2 randomtestadventurer
	./randomtestcard1 &> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov dominion.c -bf >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out


all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe 
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer randomtestresults.out
