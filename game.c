#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

void main ( int argc, char *argv[] ) {
	int poemLength;
	int playerGold;
	int playerMana;
	int roomGold, roomMana;
	FILE *resources = fopen("resources.csv", "r");
	int i = 0;
	int j = 1;
	char valuables[7];
	while (!feof(resources)) {
		char c = getc(resources);
		temp[i] = c;
		if (c == ',') {
			valuables[i] = '\0';
			if (j == 2) {
				roomMana = atoi(valuables);	
			} 
			else if (j == 1) {
				roomGold = atoi(valuables);
			}
			j++;
			i = 0;
		} 
		else  i++; 
	}
	fclose(ressources);
	char *poem;
	if ( poemLength <= 10 ) {
		printf(" Although we do believe in consiseness, there is a limit to how short a beautiful poem can be.  ");
	}
	time_t t; 
  	/* Intializes random number generator */
   	srand((unsigned) time(&t));
	printf("   Random numbers generated: \n");
	int r = rand()%10;
	printf(" %d", r);
	if (r == 9){
		printf(" That was... truly beautiful! Take all your");	
	}
	else{
		printf("Maybe you should ponder over your word choice a little more");
	}
}
