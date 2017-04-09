#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void getInput(char *dest, int *i){
    char c = getchar();
    //cut everything out until "="
    for(;c!='=';(*i)++)
        c = getchar();
    //give dest all info until "&"
    int j = *i;
    for(;c!='&'&&c!='\n';i++){
        dest[*i-j] = c;
        c = getchar();
    }
    dest[*i-j] = '\0';
}

void main ( int argc, char *argv[] ) {
    printf("1");
    int i = 0;
    //int size = atoi(getenv("CONTENT_LENGTH"));
    //printf("%d", size);
    char *command = (char*)malloc(1000);
    getInput(command, &i);
    char *poem = (char*)malloc(1000);
    getInput(poem, &i);
	int poemLength = strlen(poem);
	if ( poemLength <= 10 ) {
		printf(" Although we do believe in consiseness, there is a limit to how short a beautiful poem can be.  ");
	}
	time_t t;
  	/* Intializes random number generator */
   	srand((unsigned) time(&t));
	printf("Random numbers generated: \n");
	int r = rand()%10;
	printf(" %d", r);
	if (r == 9){
		printf(" That was... truly beautiful! Take all your");
	}
	else{
		printf("Maybe you should ponder over your word choice a little more");
	}
}
