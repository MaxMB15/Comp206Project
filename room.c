#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void toUpper(char *string);
int beginsWith(char *begin, char *str);
void getInput(char *src, char *dest, int *i);
void strcut(char *src, char *dest, int cutPlace);
int isNum(char *src);

int main ( int argc, char *argv[] ) {
    int playerGold;
    int playerMana;
    int roomGold, roomMana;
    FILE *resources = fopen("resources.csv", "r+");
    int i = 0;
    int j = 1;
    char valuables[7];
    while (!feof(resources)) {
        char c = getc(resources);
        valuables[i] = c;
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
    fclose(resources);
    
    
    //size of content given by web page
    int size = atoi(getenv("CONTENT_LENGTH"));
    //get COMMANDS
    i = 0;
    char* input = (char*)(malloc(size));
    scanf("%s",input);
    char* command = (char*)(malloc(size));
    char* tempHolder = (char *)(malloc(20));
    int commandError = 0;
    getInput(input,command,&i);
    //Make everything uppercase
    toUpper(command);
    
    int code = 0;
    
    if(strcmp(command,"PLAY")){
        code = 1;
        
    }else if(strcmp(command,"REFRESH")){
        code = 2;
        
    }else if(strcmp(command,"EXIT")){
        code = 3;
        
    }else if(beginsWith("DROP+",command)){
        strcut(command,tempHolder,strlen("DROP+"));
        if(isNum(tempHolder)){
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
    printf("<html>\n"
           "    <title>We Love Poems!</title>\n"
           "    <body>\n"
           "        <center>\n"
           "            <div>\n"
           "                <h1>\n"
           "                    <p><font color=\"white\">We Love Poems! Write down your best and we might give you Coins or Mana.</font></p>\n"
           "                </h1>\n"
           "                <!--PUT THIS IN:-->\n"
           "                <img src=\"src/room.jpg\" width=\"40%%\">\n"
           "                <h1></h1>\n"
           );
    //play game code
    if(code == 1){
        printf("                <input type=\"text\" form=\"text\" name=\"command\"></input>\n"
               "               <form action=\"cgi-bin/room.cgi\" method=\"POST\" id=\"text\"></form>\n"
               "                <form action=\"game.cgi\" method=\"POST\" id=\"poemText\">\n"
               "                    <textarea form=\"poemText\" name=\"peom\" value=\"\"></textarea></br></br>\n"
               "                    <input type=\"submit\"></input>\n"
               "                </form>\n"
               );
    }
    else{
        printf("                <input type=\"submit\" form=\"north\" name=\"north\" value=\"North\"></input></br>\n"
               "                <input type=\"submit\" form=\"east\" name=\"east\" value=\"East\"></input>\n"
               "                <input type=\"text\" form=\"text\" name=\"command\"></input>\n"
               "                <input type=\"submit\" form=\"west\" name=\"west\" value=\"West\"></input></br>\n"
               "                <input type=\"submit\" form=\"south\" name=\"south\" value=\"South\"></input>\n"
               "                    <!--teleport should edit this in:-->\n"
               "                <input type=\"hidden\" name=\"inve\" value=\"6,6\"></input>\n"
               "                <form action=\"cgi-bin/room.cgi\" method=\"POST\" id=\"text\"></form>\n"
               "                <form action=\"cgi-bin/room.cgi\" method=\"POST\" id=\"north\">\n"
               "                        <!--teleport should edit this in:-->\n"
               "                    <input type=\"hidden\" name=\"inve\" value=\"6,6\"></input>\n"
               "                                    <!--edit this to the other sites transporter.py file:-->\n"
               "                    <input type=\"hidden\" name=\"url\" value=\"http://blank\"></input>\n"
               "                </form>\n"
               "                <form action=\"cgi-bin/room.cgi\" method=\"POST\" id=\"east\">\n"
               "                        <!--teleport should edit this in:-->\n"
               "                    <input type=\"hidden\" name=\"inve\" value=\"6,6\"></input>\n"
               "                                    <!--edit this to the other sites transporter.py file:-->\n"
               "                    <input type=\"hidden\" name=\"url\" value=\"http://blank\"></input>\n"
               "                </form>\n"
               "                <form action=\"cgi-bin/room.cgi\" method=\"POST\" id=\"west\">\n"
               "                        <!--teleport should edit this in:-->\n"
               "                    <input type=\"hidden\" name=\"inve\" value=\"6,6\"></input>\n"
               "                                    <!--edit this to the other sites transporter.py file:-->\n"
               "                    <input type=\"hidden\" name=\"url\" value=\"http://blank\"></input>\n"
               "                </form>\n"
               "                <form action=\"cgi-bin/room.cgi\" method=\"POST\" id=\"south\">\n"
               "                        <!--teleport should edit this in:-->\n"
               "                    <input type=\"hidden\" name=\"inve\" value=\"6,6\"></input>\n"
               "                                    <!--edit this to the other sites transporter.py file:-->\n"
               "                    <input type=\"hidden\" name=\"url\" value=\"http://blank\"></input>\n"
               "                </form>\n"
               );}
    printf("            </div>\n"
           "        </center>\n"
           "    </body>\n"
           "    <style>\n"
           "        @font-face {\n"
           "            font-family: Distant_Stroke;\n"
           "            src: url(\"src/Distant_Stroke.otf\") format(\"opentype\");\n"
           "        }\n"
           "        body {\n"
           "            height: 100%%;\n"
           "            margin: 0;\n"
           "            padding: 0;\n"
           "            background-color: #FFCC00;\n"
           "            background: url(\"src/bg.jpg\");\n"
           "            background-size: 100%% 100%%;\n"
           "            font-family: Distant_Stroke;\n"
           "            font-size: 30px;\n"
           "        }\n"
           "        input[type=submit] {\n"
           "            width: 20%%;  height: 10%%;\n"
           "            font-family: Distant_Stroke;\n"
           "            font-size: 40px;\n"
           "            text-align: center;\n"
           "        }\n"
           "        input[type=text] {\n"
           "            padding: 0px;\n"
           "            width: 20%%;  height: 7%%;\n"
           "            font-family: Distant_Stroke;\n"
           "            font-size: 40px;\n"
           "            text-align: center;\n"
           "        }\n"
           );
    //play game code
    if(code==1){
        printf("        textarea {\n"
               "            height: 40%%;\n"
               "            width: 40%%;\n"
               "            margin: 0;\n"
               "            padding: 20px;\n"
               "        }\n"
               );
    }
    printf("    </style>\n"
           "</html>\n"
           );
    
    return 0;
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
    dest[i-cutPlace]='\n';
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



