#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Generate any ASCII character
   int r_val = rand() % (126 + 1 - 32) + 32;
   return r_val;
}

char *inputString(char istring[])
{
    memset(istring, '\0', 6);
     int i;
    for (i = 0; i<5; i++)
    {
	//Generate random lower case character
	char aChar = "RrEeSsTt"[random()%8] ; //rand()% (122+1-97)+97; //97
  	istring[i] = aChar;
    }
   return istring;
}


void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    char istring[6];
    tcCount++;
    c = inputChar();
    s = inputString(istring);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
    //printf("istring 1 is %c 3 is %c 5 is %c\n", s[1], s[3], s[5]);
    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
