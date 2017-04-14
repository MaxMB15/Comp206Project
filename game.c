#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

int main ( int argc, char *argv[] ) {
     //get room resources
    
	int roomGold, roomMana;
	FILE *resources = fopen("resources.csv", "r");
	char *roomResources = (char *)(malloc(40));
	fscanf(resources,"%s",roomResources);
	fclose(resources);
	getInv(roomResources, &roomMana, &roomGold);

	int size = atoi(getenv("CONTENT_LENGTH"));
	//printf("size %d \n", size);
	printf("1");
	
	//Read input
	char* input = (char*)(malloc(size));
	scanf("%s",input);
	printf("1");
	//printf("%s", input);

	int i = 0;
	char *poem = (char*)malloc(size);
	getInput(input, poem, &i);

	int poemLength = strlen(poem);

	printf("1");

	//get inventory
	char* inv = (char*)(malloc(size));
	getInput(input,inv,&i);
	int playerMana = 0;
	int playerGold = 0;
	getInv(inv, &playerMana, &playerGold);
	
	if(!strcmp("3a14159q165", poem)){
		printf("Content-Type:text/html\n\n");
        	printf("<html>\n");
        	printf("    <title>We Love Poems!</title>\n");
        	printf("    <body>\n");
        	printf("        <center>\n");
        	printf("            <div>\n");
        	printf("                <h1>\n");
        	printf("                    <p><font color=\"white\">Congratulations, you have won the game!</font></p>\n");
        	printf("                </h1>\n");
		char *temp = (char*)(malloc(size));
		getInput(input,temp,&i);
		int tempPlayerMana = atoi(temp);
		int a = 0;
		if(tempPlayerMana>roomMana){
			a++;
			printf("			<form action=\"game.cgi\" method=\"POST\"><input value=\"3a14159q165\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"><input value=\"mana\" type=\"text\" name=\"mana\"><input value=\"gold\" type=\"text\" name=\"gold\"></br><input value=\"submit\" type=\"submit\" name=\"submit\"></form>",playerMana, playerGold);
		}
		getInput(input,temp,&i);
		int tempPlayerGold =atoi(temp);
		if(tempPlayerGold > roomGold && a==0){
			printf("			<form action=\"game.cgi\" method=\"POST\"><input value=\"3a14159q165\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"><input value=\"mana\" type=\"text\" name=\"mana\"><input value=\"gold\" type=\"text\" name=\"gold\"></br><input value=\"submit\" type=\"submit\" name=\"submit\"></form>",playerMana, playerGold);
		}
		else if(tempPlayerMana + tempPlayerGold > 5 || tempPlayerMana < 0 || tempPlayerGold < 0){
			printf("			<form action=\"game.cgi\" method=\"POST\"><input value=\"3a14159q165\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"><input value=\"mana\" type=\"text\" name=\"mana\"><input value=\"gold\" type=\"text\" name=\"gold\"></br><input value=\"submit\" type=\"submit\" name=\"submit\"></form>",playerMana, playerGold);
		}
		printf("                <h2>\n");
		printf("                    <p><font color=\"white\">You have %d gold, and %d manna. Our room has %d gold, and %d manna.</font></p>\n", playerGold, playerMana, roomGold, roomMana);
		printf("                </h2>\n");
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
        	printf("    </style>\n");
        	printf("</html>\n");
		return 0;
	}
	
	if(playerGold >= 100){        
        	printf("Content-Type:text/html\n\n");
        	printf("<html>\n");
        	printf("    <title>We Love Poems!</title>\n");
        	printf("    <body>\n");
        	printf("        <center>\n");
        	printf("            <div>\n");
        	printf("                <h1>\n");
        	printf("                    <p><font color=\"white\">Congratulations, you have won the game!</font></p>\n");
        	printf("                </h1>\n");
		printf("                <h2>\n");
		printf("                    <p><font color=\"white\">You have %d gold, and %d manna. Our room has %d gold, and %d manna.</font></p>\n", playerGold, playerMana, roomGold, roomMana);
		printf("                </h2>\n");
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
        	printf("    </style>\n");
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

	if ( poemLength <= 10 ) {
		printf("                    <p><font color=\"white\">Although we do believe in consiseness, there is a limit to how short a beautiful poem can be.</font></p>\n");
		printf("			<form action=\"room.cgi\" method=\"POST\"><input value=\"Try again\" type=\"submit\"><input value=\"Play\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"></form>",playerMana, playerGold);
	}
	else if (poemLength >250) {
		printf("                    <p><font color=\"white\">We do believe in consiseness, there is a limit to how long a beautiful poem can be.</font></p>\n");
		printf("			<form action=\"room.cgi\" method=\"POST\"><input value=\"Try again\" type=\"submit\"><input value=\"Play\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"></form>",playerMana, playerGold);
	}
	else if ((strstr(poem, "rose") != NULL)||(strstr(poem, "violet") != NULL)||(strstr(poem, "flower") != NULL)) {
		printf("                    <p><font color=\"white\">We love flowers! Well written!</font></p>\n");
		printf("			<form action=\"game.cgi\" method=\"POST\"><input value=\"3a14159q165\" type=\"hidden\" name=\"command\"><input value=\"%d,%d\" type=\"hidden\" name=\"inventory\"><input value=\"mana\" type=\"text\" name=\"mana\"><input value=\"gold\" type=\"text\" name=\"gold\"></br><input value=\"submit\" type=\"submit\" name=\"submit\"></form>",playerMana, playerGold);
	}
	else if (r == 1){
        	printf("                    <p><font color=\"white\">That was... truly beautiful! Take all your the amount of gold or mana you want!</font></p>\n");
	}
	else{
        printf("                    <p><font color=\"white\">Maybe you should ponder over your word choice a little more</font></p>\n");
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
