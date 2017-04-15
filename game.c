#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Gets the input and puts into dest
void getInput(char *src, char *dest, int *i){
    char c = ' ';
    //cut everything out until "="
    for(;c!='=';(*i)++)
        c = src[*i];
    c = src[*i];
    (*i)++;
    
    //give dest all info until "&"
    int j = *i;
    for(;c!='&'&&c!='\0';(*i)++){
        dest[*i-j] = c;
        c = src[*i];
    }
    dest[*i-j] = '\0';
}

//Gets inventory
void getInv(char *data, int *mana, int *gold){
    //parse through data
    char *buffer = (char *)(malloc(20));
    int afterComma = 0;
    int i, j = 0;
    for(i=0;i<strlen(data);i++){
        //search for comma
        if(data[i]=='%'&&data[i+1]=='2'&&data[i+2]=='C'){
            if(afterComma)
                break;
            afterComma = 1;
            buffer[i] = '\0';
            *mana = atoi(buffer);
            i+=2;
            j = i+1;
            continue;
        }
        else if(data[i]==','){
            if(afterComma)
                break;
            afterComma = 1;
            buffer[i] = '\0';
            *mana = atoi(buffer);
            j = i+1;
            continue;
        }
        if(!afterComma){
            buffer[i] = data[i];
        }
        else{
            buffer[i-j] = data[i];
        }
    }
    buffer[i-j] = '\0';
    *gold = atoi(buffer);
    free(buffer);
    
}

//Checks if char is an integer
int isNum(char *src){
    int i;
    for(i=0;i<strlen(src);i++){
        if(src[i]<'0'||src[i]>'9'){
            return 1;
        }
    }
    return 0;
}

int main ( int argc, char *argv[] ) {
	//get room resources
	int roomGold, roomMana;
	FILE *resources = fopen("resources.csv", "r");
	char *roomResources = (char *)(malloc(40));
	fscanf(resources,"%s",roomResources);
	fclose(resources);
	getInv(roomResources, &roomMana, &roomGold);

	int size = atoi(getenv("CONTENT_LENGTH")); //Gets size of input
	
	//Read input
	char* input = (char*)(malloc(size));
	scanf("%s",input);
	
	int i = 0;
	char *poem = (char*)malloc(size);
	getInput(input, poem, &i);

	int poemLength = strlen(poem);

	//get inventory
	char* inv = (char*)(malloc(size));
	getInput(input,inv,&i);
	int playerMana = 0;
	int playerGold = 0;
	getInv(inv, &playerMana, &playerGold);
	
	if(!strcmp("3a141qfsdasx3hfdg3259q165", poem)){ //meaning they have won our game
		printf("Content-Type:text/html\n\n");
        	printf("<html>\n");
        	printf("    <title>We Love Poems!</title>\n");
        	printf("    <body>\n");
        	printf("        <center>\n");
        	printf("            <div>\n");
		char *temp = (char*)(malloc(size));
		getInput(input,temp,&i); //Gets the manna the player entered
		int tempPlayerMana = atoi(temp); 
		int a = 0;
		int b = 0;
		if(tempPlayerMana>roomMana||isNum(temp)){ //Checks if wanted manna is valid
			a++;
			b++;
		}
		getInput(input,temp,&i);
		int tempPlayerGold =atoi(temp); ////Gets the gold the player entered
		if((tempPlayerGold > roomGold && a==0)||isNum(temp)){ //Checks if wanted gold is valid
			b++;
		}
		else if(a == 0 && (tempPlayerMana + tempPlayerGold > 5 || tempPlayerMana < 0 || tempPlayerGold < 0)){ //Checks if the values are positive and are not more than 5
			b++;		
		}
		if(b>0){ //The format was not correct
			printf("                <h1>\n");
        		printf("                    <p><font color=\"white\">Please enter a valid amount</font></p>\n");
        		printf("                </h1>\n");
			printf("			<form action=\"game.cgi\" method=\"POST\"><input value=\"3a141qfsdasx3hfdg3259q165\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"><input value=\"Manna\" type=\"text\" name=\"mana\"><input value=\"Gold\" type=\"text\" name=\"gold\"></br><input value=\"Submit\" type=\"submit\" name=\"submit\"></form>",playerMana, playerGold);
		}
		if(playerGold>100){ //Means the player has won
        		printf("                <h1>\n");
        		printf("                    <p><font color=\"white\">Congratulations, you have won the game!</font></p>\n");
        		printf("                </h1>\n");
		}
		else if (b==0){ 
			printf("                <h2>\n");
			printf("                    <p><font color=\"white\">You have %d manna, and %d gold. Our room has %d manna, and %d gold.</font></p>\n", playerMana+tempPlayerMana, playerGold+tempPlayerGold , roomMana-tempPlayerMana , roomGold-tempPlayerGold);
			printf("                </h2>\n");
			FILE *write = fopen("resources.csv", "w");
			fprintf(write, "%d,%d,1", roomMana-tempPlayerMana, roomGold-tempPlayerGold);
			fclose(write);
			printf("			<form action=\"room.cgi\" method=\"POST\"><input value=\"Home page\" type=\"submit\"><input value=\"refresh\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"></form>",playerMana+tempPlayerMana , playerGold+tempPlayerGold);
		}
		else{
			printf("                <h2>\n");
			printf("                    <p><font color=\"white\">You have %d manna, and %d gold. Our room has %d manna, and %d gold.</font></p>\n", playerMana, playerGold, roomMana, roomGold);
			printf("                </h2>\n");
		}
        	printf("            </div>\n");
        	printf("        </center>\n");
        	printf("    </body>\n");
        	printf("    <style>\n");
		printf("        @font-face {\n");
		printf("            font-family: Distant_Stroke;\n");
		printf("            src: url(\"../src/Distant_Stroke.otf\") format(\"opentype\");\n");
		printf("        }\n");
		printf("        body {\n");
		printf("            height: 100%%;\n");
		printf("            margin: 0;\n");
		printf("            padding: 0;\n");
		printf("            background-color: #FFCC00;\n");
		printf("            background: url(\"../src/bg.jpg\");\n");
		printf("            background-size: 100%% 100%%;\n");
		printf("            font-family: Distant_Stroke;\n");
		printf("            font-size: 30px;\n");
		printf("        }\n");
		printf("        input[type=submit] {\n");
		printf("            width: 20%%;  height: 10%%;\n");
		printf("            font-family: Distant_Stroke;\n");
		printf("            font-size: 40px;\n");
		printf("            text-align: center;\n");
		printf("        }\n");
		printf("        input[type=text] {\n");
		printf("            padding: 0px;\n");
		printf("            width: 20%%;  height: 7%%;\n");
		printf("            font-family: Distant_Stroke;\n");
		printf("            font-size: 40px;\n");
		printf("            text-align: center;\n");
		printf("        }\n");        printf("    </style>\n");
        	printf("</html>\n");
		return 0;
	}
	
	time_t t;
  	// Intializes random number generator 
   	srand((unsigned) time(&t));
	printf("Random numbers generated: \n");
	int r = rand()%3;
	printf(" %d", r);

	printf("Content-Type:text/html\n\n");
        printf("<html>\n");
        printf("    <title>We Love Poems!%s</title>\n", input);
        printf("    <body>\n");
        printf("        <center>\n");
        printf("            <div>\n");
        printf("                <h2>\n");
	printf("                    <p><font color=\"white\">You wrote:\n%s</font></p>\n", poem);
        printf("                </h2>\n");
        printf("                <h1>\n");

	if ( poemLength <= 10 ) { //Poem is too short
		printf("                    <p><font color=\"white\">Although we do believe in consiseness, there is a limit to how short a beautiful poem can be.</font></p>\n");
		printf("			<form action=\"room.cgi\" method=\"POST\"><input value=\"Try again\" type=\"submit\"><input value=\"Play\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"></form>",playerMana, playerGold);
	}
	else if (poemLength >250) { //Poem is too long
		printf("                    <p><font color=\"white\">We do believe in consiseness, there is a limit to how long a beautiful poem can be.</font></p>\n");
		printf("			<form action=\"room.cgi\" method=\"POST\"><input value=\"Try again\" type=\"submit\"><input value=\"Play\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"></form>",playerMana, playerGold);
	}
	else if ((strstr(poem, "rose") != NULL)||(strstr(poem, "violet") != NULL)||(strstr(poem, "flower") != NULL)) { //Poem contains flowers!!
		printf("                    <p><font color=\"white\">We love flowers! Well written!</font></p>\n");
		printf("                    <p><font color=\"white\">You have %d manna, and %d gold. Our room has %d manna, and %d gold.</font></p>\n", playerMana, playerGold, roomMana, roomGold);
		printf("			<form action=\"game.cgi\" method=\"POST\"><input value=\"3a141qfsdasx3hfdg3259q165\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"><input value=\"Manna\" type=\"text\" name=\"mana\"><input value=\"Gold\" type=\"text\" name=\"gold\"></br><input value=\"Submit\" type=\"submit\" name=\"submit\"></form>",playerMana, playerGold);
	}
	else if (r == 1){ //Random number generator thinks it is a good poem
        	printf("                    <p><font color=\"white\">That was... truly beautiful! Take all your the amount of gold or mana you want!</font></p>\n");
		printf("                    <p><font color=\"white\">You have %d manna, and %d gold. Our room has %d manna, and %d gold.</font></p>\n", playerMana, playerGold, roomMana, roomGold);
		printf("			<form action=\"game.cgi\" method=\"POST\"><input value=\"3a141qfsdasx3hfdg3259q165\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"><input value=\"Manna\" type=\"text\" name=\"mana\"><input value=\"Gold\" type=\"text\" name=\"gold\"></br><input value=\"Submit\" type=\"submit\" name=\"submit\"></form>",playerMana, playerGold);
	}
	else{ //Not a good poem, asks to try again
		printf("                    <p><font color=\"white\">Maybe you should ponder over your word choice a little more</font></p>\n");
		printf("			<form action=\"room.cgi\" method=\"POST\"><input value=\"Try again\" type=\"submit\"><input value=\"Play\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"></form>",playerMana, playerGold);
	}
        printf("                </h1>\n");
        printf("            </div>\n");
        printf("        </center>\n");
        printf("    </body>\n");
        printf("    <style>\n");
	printf("        @font-face {\n");
	printf("            font-family: Distant_Stroke;\n");
	printf("            src: url(\"../src/Distant_Stroke.otf\") format(\"opentype\");\n");
	printf("        }\n");
	printf("        body {\n");
	printf("            height: 100%%;\n");
	printf("            margin: 0;\n");
	printf("            padding: 0;\n");
	printf("            background-color: #FFCC00;\n");
	printf("            background: url(\"../src/bg.jpg\");\n");
	printf("            background-size: 100%% 100%%;\n");
	printf("            font-family: Distant_Stroke;\n");
	printf("            font-size: 30px;\n");
	printf("        }\n");
	printf("        input[type=submit] {\n");
	printf("            width: 20%%;  height: 10%%;\n");
	printf("            font-family: Distant_Stroke;\n");
	printf("            font-size: 40px;\n");
	printf("            text-align: center;\n");
	printf("        }\n");
	printf("        input[type=text] {\n");
	printf("            padding: 0px;\n");
	printf("            width: 20%%;  height: 7%%;\n");
	printf("            font-family: Distant_Stroke;\n");
	printf("            font-size: 40px;\n");
	printf("            text-align: center;\n");
	printf("        }\n");        printf("    </style>\n");
        printf("</html>\n");
	return 0;
}
