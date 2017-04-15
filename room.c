#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void getInv(char *data, int *mana, int *gold);
char getFromLoc(char *data);
void toUpper(char *string);
int beginsWith(char *begin, char *str);
void getInput(char *src, char *dest, int *i);
void strcut(char *src, char *dest, int cutPlace);
int isNum(char *src);

int main ( int argc, char *argv[] ) {
    //get room resources
    int roomGold, roomMana;
    FILE *resources = fopen("resources.csv", "r");
    int i = 0;
    char *roomResources = (char *)(malloc(40));
    fscanf(resources,"%s",roomResources);
    fclose(resources);
    getInv(roomResources, &roomMana, &roomGold);
    
    //size of content given by web page
    //int size = atoi(getenv("CONTENT_LENGTH"));
    int size = 50;
    //Get data
    char* input = (char*)(malloc(size));
    scanf("%s",input);
    
    //get commands
    i = 0;
    char* command = (char*)(malloc(size));
    char* tempHolder = (char *)(malloc(20));
    int commandError = 0;
    getInput(input,command,&i);
    //Make everything uppercase
    toUpper(command);
    
    //get inventory
    char* inv = (char*)(malloc(size));
    getInput(input,inv,&i);
    int playerMana = 0;
    int playerGold = 0;
    getInv(inv, &playerMana, &playerGold);
    
    //Make sure location comes from room page
    //normal char is c
    //game char is i
    char location = getFromLoc(input);
    if(location=='i'){
        strcpy(command, "PLAY");
        commandError = 1;
    }
    
    //Handle commands
    if(!strcmp(command,"EXIT")){
        resources = fopen("resources.csv", "w");
        fprintf(resources,"%d,%d,0",roomMana, roomGold);
        fclose(resources);
        
        printf("Content-Type:text/html\n\n");
        printf("<html>\n");
        printf("    <title>We Love Poems!</title>\n");
        printf("    <body>\n");
        printf("        <center>\n");
        printf("            <div>\n");
        printf("                <h1>\n");
        printf("                    <p><font color=\"white\">We are sorry that you wanted to leave.</font></p>\n");
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
        printf("    </style>\n");
        printf("</html>\n");
        return 0;
    }
    
    int code = 0;
    if(!strcmp(command,"PLAY")){
        code = 1;
        
    }else if(!strcmp(command,"REFRESH")){
        code = 2;
        
    }else if(!beginsWith("DROP+",command)){
        strcut(command,tempHolder,strlen("DROP+"));
        if(!isNum(tempHolder)){
            int dropNum = atoi(tempHolder);
            if(dropNum>playerGold){
                //tried dropping more gold then what they had.
                commandError = 5;
            }
            else{
                playerMana+=dropNum/2;
                playerGold-= dropNum;
                code = 4;
            }
        }
        else{
            //not a number input
            commandError = 2;
        }
    }
    else{
        //INVALID COMMAND
        commandError = 1;
    }
    
    
    
    
    printf("Content-Type:text/html\n\n");
    printf("<html>\n");
    printf("    <title>We Love Poems!</title>\n");
    printf("    <body>\n");
    printf("        <center>\n");
    printf("            <div>\n");
    printf("                <h1>\n");
    printf("                    <p><font color=\"white\">We Love Poems! Write down your best and we might give you Coins or Mana.</font></p>\n");
    printf("                </h1>\n");
    printf("                <img src=\"../src/room.jpg\" width=\"40%%\">\n");
    
    //Error codes
    if(commandError == 1)
        printf("                <h1>This is an invalid command.</h1>\n");
    else if(commandError == 2)
        printf("                <h1>Drop number not valid.</h1>\n");
    else if(commandError == 5)
        printf("                <h1>Not enough gold to drop.</h1>\n");
    else if(code == 4)
        printf("                <h1>You now have %d manna and %d gold.</h1>\n",playerMana, playerGold);
    else
        printf("                <h1></h1>\n");
    
    
    //play game code
    if(code == 1){
        printf("                <form action=\"room.cgi\" method=\"POST\" id=\"inp\"></form>\n");
        printf("                <input type=\"text\" form=\"inp\" name=\"text\"></input>\n");
        printf("                <input type=\"hidden\" form=\"inp\" name=\"inventory\" value=\"%d,%d\"></input>\n",playerMana, playerGold);
        printf("                <form action=\"game.cgi\" method=\"POST\" id=\"poemText\">\n");
        printf("                    <textarea form=\"poemText\" name=\"poem\" value=\"\"></textarea></br></br>\n");
        printf("                    <input form=\"poemText\" type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></input>\n",playerMana, playerGold);
        printf("                    <input form=\"poemText\" type=\"submit\"></input>\n");
        printf("                </form>\n");
    }
    else{
        printf("                <input type=\"submit\" form=\"north\" name=\"north\" value=\"North\"></input></br>\n");
        printf("                <input type=\"submit\" form=\"east\" name=\"east\" value=\"East\"></input>\n");
        printf("                <input type=\"text\" form=\"text\" name=\"command\"></input>\n");
        printf("                <input type=\"submit\" form=\"west\" name=\"west\" value=\"West\"></input></br>\n");
        printf("                <input type=\"submit\" form=\"south\" name=\"south\" value=\"South\"></input>\n");
        printf("                <input type=\"hidden\" form=\"text\" name=\"inventory\" value=\"%d,%d\"></input>\n",playerMana, playerGold);
        printf("                <form action=\"room.cgi\" method=\"POST\" id=\"text\"></form>\n");
        printf("                <form action=\"room.cgi\" method=\"POST\" id=\"north\">\n");
        printf("                        <!--teleport should edit this in:-->\n");
        printf("                    <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></input>\n",playerMana, playerGold);
        printf("                                    <!--edit this to the other sites transporter.py file:-->\n");
        printf("                    <input type=\"hidden\" name=\"url\" value=\"http://blank\"></input>\n");
        printf("                </form>\n");
        printf("                <form action=\"room.cgi\" method=\"POST\" id=\"east\">\n");
        printf("                        <!--teleport should edit this in:-->\n");
        printf("                    <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></input>\n",playerMana, playerGold);
        printf("                                    <!--edit this to the other sites transporter.py file:-->\n");
        printf("                    <input type=\"hidden\" name=\"url\" value=\"http://www.cs.mcgill.ca/~lerbay/cgi-bin/transporter.py\"></input>\n");
        printf("                </form>\n");
        printf("                <form action=\"room.cgi\" method=\"POST\" id=\"west\">\n");
        printf("                        <!--teleport should edit this in:-->\n");
        printf("                    <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></input>\n",playerMana, playerGold);
        printf("                                    <!--edit this to the other sites transporter.py file:-->\n");
        printf("                    <input type=\"hidden\" name=\"url\" value=\"http://blank\"></input>\n");
        printf("                </form>\n");
        printf("                <form action=\"room.cgi\" method=\"POST\" id=\"south\">\n");
        printf("                        <!--teleport should edit this in:-->\n");
        printf("                    <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></input>\n",playerMana, playerGold);
        printf("                                    <!--edit this to the other sites transporter.py file:-->\n");
        printf("                    <input type=\"hidden\" name=\"url\" value=\"http://blank\"></input>\n");
        printf("                </form>\n");
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
    printf("        }\n");
    
    //play game code
    if(code==1){
        printf("        textarea {\n");
        printf("            height: 40%%;\n");
        printf("            width: 40%%;\n");
        printf("            margin: 0;\n");
        printf("            padding: 20px;\n");
        printf("        }\n");
    }
    printf("    </style>\n");
    printf("</html>\n");
    
    free(inv);
    free(input);
    free(command);
    free(tempHolder);
    
    return 0;
}


char getFromLoc(char *data){
    //search for '?'
    int i;
    for(i=0;i<strlen(data);i++){
        if(data[i]=='?'){
            return data[i+1];
        }
    }
    return '\n';
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
void toUpper(char *string){
    int i;
    for(i=0;i<strlen(string);i++){
        string[i] = toupper(string[i]);
    }
}
int beginsWith(char *begin, char *str){
    if(strlen(begin)>strlen(str)){
        return 1;
    }
    int i;
    for(i = 0;i<strlen(begin);i++){
        if(begin[i]!=str[i]){
            return 1;
        }
    }
    return 0;
}
//takes the upper part after cutPlace
void strcut(char *src, char *dest, int cutPlace){
    int i;
    for(i=cutPlace;i<strlen(src);i++){
        dest[i-cutPlace] = src[i];
    }
    dest[i-cutPlace]='\0';
}
int isNum(char *src){
    int i;
    for(i=0;i<strlen(src);i++){
        if(src[i]<'0'||src[i]>'9'){
            return 1;
        }
    }
    return 0;
}



