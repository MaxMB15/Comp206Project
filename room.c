#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void toUpper(char *string);

void main ( int argc, char *argv[] ) {
	int poemLength;
	int playerGold;
	int playerMana;
	int roomGold, roomMana;
	FILE *resources = fopen("resources.csv", "r+");
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
    //size of content given by web page
    int size = atoi(getenv("CONTENT_LENGTH"));
    //GET COMMANDS
    int i = 0;
    char* command = (char*)(malloc(size));
    getInput(command,&i);

    if(strcmp(toUpper(command),"PLAY"))

        printf("Content-Type:test/html\n\n");
    printf("<html>\n"
           "<title>We Love Poems!</title>"
           "<body>\n"
           "<center>\n"
           "<div>\n"
           "<h1>\n"
           "<p><font color=\"white\">We Love Poems! Write down your best and we might give you Coins or Mana.</font></p>\n"
           "</h1>\n"
           "<!--PUT THIS IN:-->\n"
           "<img src=\"src/room.jpg\" width=\"40%\">\n"
           "<h1></h1>\n"
           "<form action=\"cgi-bin/command.cgi\" method=\"post\">\n"
           "<input type=\"button\" name=\"north\" value=\"North\"></input></br>\n"
           "<input type=\"button\" name=\"east\" value=\"East\"></input>\n"
           "<input type=\"text\" name=\"command\"></input>\n"
           "<input type=\"button\" name=\"west\" value=\"West\"></input></br>\n"
           "<input type=\"button\" name=\"south\" value=\"South\"></input>\n"
           "<!--teleport should edit this in:-->\n"
           "<input type=\"hidden\" name=\"inve\" id=\"inv\" value=\"666\"></input>\n"
           "</form>\n"
           "</div>\n"
           "</center>\n"
           "</body>\n"
           "<style>\n"
           "@font-face {\n"
           "    font-family: Distant_Stroke;\n"
           "src: url(\"src/Distant_Stroke.otf\") format(\"opentype\");\n"
           "}\n"
           "body {\n"
           "height: 100%;\n"
           "margin: 0;\n"
           "padding: 0;\n"
           "    background-color: #FFCC00;\n"
           "background: url(\"src/bg.jpg\");\n"
           "    background-size: 100% 100%;\n"
           "    font-family: Distant_Stroke;\n"
           "    font-size: 30px;\n"
           "}\n"
           "input[type=button] {\n"
           "width: 20%;  height: 10%;\n"
           "}\n"
           "input[type=text] {\n"
           "padding: 0px;\n"
           "width: 20%;  height: 7%;\n"
           "    font-family: Distant_Stroke;\n"
           "    font-size: 40px;\n"
           "    text-align: center;\n"
           "}\n"
           "</style>\n"
           "</html>");\n"
        "}\n"
    );
    return 0;
}


void getInput(char *dest, int *i){
    char c = getchar();
    //cut everything out until "="
    for(;c!='=';(*i)++)
        c = getchar();
    //give dest all info until "&"
    int j = *i;
    for(;c!='&'&&c!='\0';i++){
        dest[*i-j] = c;
        c = getchar();
    }
    dest[*i-j] = '\0';
}
void toUpper(char *string){
    int i;
    for(i=0;i<strlen(string);i++){
        string[i] = toupper(string[i]);
    }
}
           
           

