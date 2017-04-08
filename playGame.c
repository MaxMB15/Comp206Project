#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (int argc, char argv[]) {
	char *data = getenv("QUERY_STRING");
	char *command = malloc(100*sizeof(char));
	char *inventory = malloc(100*sizeof(char));
	int inplay = 1; // 0 for in play, 1 for not in play, 2 for has won, 3 to prevent replaying, 4 when the player has exited
	int gold;
	int mana;
	int i = 0; int count = 1; int j = 0; //Counters for while loops
	int invalid = 1; // 0 for invalid command
	int roomGold;
	int roomMana;
	int badValue = 2; // 0 if gold wanted > 5 (greedy players), 1 if the room doesnt have the ressources
	char temp[4]; //Temporary string to build the variables
	//Reads the room ressources from the csv and the closes the file stream
	FILE *ressources = fopen("../roomRessources.csv", "r");
	while (!feof(ressources)) {
		char c = getc(ressources);
		temp[i] = c;
		if (c == ',') {
			temp[i] = '\0';
			if (count == 1) {
				roomGold = atoi(temp);	
			} else if (count == 2) {
				roomMana = atoi(temp);
			}
			count++;
			i = 0;
		} else  i++; 
	}
	fflush(ressources);
	fclose(ressources);
	//Reopens the csv file to be overwriten if necessary
	FILE *newRessources = fopen("../roomRessources.csv", "w");
	char overwrite[12]; // The string char to be created to overwrite the csv
	i = 0; count = 1; j = 0;
	//Separates into the command, the inventory and whether inplay or not(to remove teleporters)
	while (data[i] != '\0') {
		if (data[i] == '=') {
			if (count == 1) {//Sets up the command part
				i++;
				while (data[i] != '&') {
					command[j] = data[i];
					i++;
					j++;	
				}
				command[j] = '\0';
				j = 0;
				count++;
			}
			else if (count == 2) {//Sets up the inventory
				i++;
				while (data[i] != '&') {
					inventory[j] = data[i];
					i++;
					j++;	
				}
				inventory[j] = '\0';
				j=0;
				count++;
			}
			else if (count == 3) {//Sets up the int indicating in play or not or won
				char *temp = malloc(2*sizeof(char));
				temp[0] = data[i+1];
				temp[1] = '\0';
				inplay = atoi(temp);
				i++;
			}
		}
		i++;
	}
	// Initial overwrite
	sprintf(overwrite, "%d,%d,1", roomGold, roomMana);
	//Sets up user gold
	i = 0; j = 0;
	while (inventory[i] != '%') {
		temp[j] = inventory[i];
		i++; j++; 
	}
	temp[j]='\0';
	gold = atoi(temp);
	j=0;i += 3;
	//sets up user mana
	while (inventory[i] != '\0') {
		temp[j] = inventory[i];
		i++; j++;
	}
	temp[j]='\0';
	mana = atoi(temp);
	
	// If no mana the player lost we steal his gold
	if (mana == 0) { 
		sprintf(overwrite, "%d,%d,0",(roomGold+gold),roomMana);
	}
	// If in play mode and QUIT is entered leave play mode
	else if (strcmp(command, "QUIT")==0 && inplay == 0){
		inplay = 1;
	}
	// If EXIT typed at any moment add their gold to the room and put their gold to 0 and room no longer occupied
	else if (strcmp(command, "EXIT") == 0) {
		sprintf(overwrite, "%d,%d,0",(roomGold+gold),(roomMana+mana));
		gold = 0;
		mana = 0;
		inplay = 4;
	}
	//If play is entered or riddle switch to play mode (RIDDLE will rewrite the riddle on screen)
	else if (strcmp(command, "PLAY")==0 || strcmp(command, "RIDDLE")== 0){
		inplay = 0;
	}
	//Don't need to do anything to refresh
	else if (strcmp(command, "REFRESH")==0);
	//If right answer entered and in play mode switch to won mode (waiting for reward)
	else if (strcmp(command, "HORIZON")==0 && inplay == 0) {
		inplay = 2;
	// If you are in win mode the int written will be given (if appropriate value)
	} else if (inplay == 2) {
		int value = atoi(command);
		if (value > roomGold || (5-value) > roomMana)
			badValue = 1;
		else if (value > 5) badValue = 0;
		else {
			gold += value;
			mana += (5-value);
			sprintf(overwrite, "%d,%d,1",roomGold-value, roomMana-(5-value));
			inplay = 3;
		}	
	}
	//For drop or invalid
	else {
		i = 5; j = 0;
		while (command[i] != '\0') {
			temp[j] = command[i];
			i++; j++;
		}
		temp[j] = '\0';
		int value = atoi(temp);
		command[4] = '\0';
		// If Drop is the command
		if (strcmp(command, "DROP")==0) {
			mana = mana + value/2;
			gold = gold - value;
			char overwrite[100];
			sprintf(overwrite, "%d,%d,1",(roomGold+value),roomMana);
			fputs(overwrite, newRessources);
		}
		//Invalid command
		else invalid = 0;
	}
	// CSS Style for the HTML page
	printf("Content-Type:text/html\n\n");
	printf("<html>");
	printf("<head>");
	printf("<title>YouGotToThink</title>");
	printf("<style>");
	printf("div.box {position: relative;width: 100%%;height: 75%%;}");
	printf("#i01 {width: 100%%;position: absolute;z-index:-1;}");
	printf("#i02 {z-index: 1;position: absolute;}");
	printf("table {position: absolute;z-index: 2;padding: 0;text-align: center;font-size: 22px;color: red;top: -8;left: -8;}");
	printf("div.play {height: 30%%;position: relative;text-align: center;font-size: 200%%;}");
	printf("div.topRow {width: 100%%;}");
	printf("div.midRow {width: 100%%;}");
	printf("div.west {width: 40%%;float: left;}");
	printf("div.east {width: 40%%;float: left;}");
	printf("div.inputBox {width: 20%%;float: left;}");
	printf("div.botRow {width: 100%%;}");
	printf("div.ret {position: absolute;border-width: 4px;border-style: solid;width: 30%%;left: 35%%;z-index: 3;font-size: 150%%;text-align: center;}");
	printf("</style>");
	printf("</head>");
	// The division of the page
	printf("<div class=\"box\">");
	printf("<img id=\"i01\" src=\"http://cs.mcgill.ca/~bkuzak1/room.jpg\" />");
	printf("<img id=\"i02\" src=\"http://cs.mcgill.ca/~bkuzak1/lootbox.jpg\" width=\"250\" />");
	printf("<table cellpadding=\"14\" cellspacing=\"8\">");
	printf("<tr><td><b>Ressources<b></td><td><b>Amount<b></td></tr>");
	printf("<tr><td><b>  Gold    <b></td><td><b>  %d   <b></td></tr>",gold);
	printf("<tr><td><b>  Mana    <b></td><td><b>  %d   <b></td></tr>",mana);
	printf("</table>");
	printf("<div class=\"ret\">");
	// The return text depending on command and score
	if (strcmp(command, "EXIT") == 0) {
	printf("<p>Sorry to see you leave<p>Your gold and mana has been added to the room and has been place unnoccupied. You are free to leave</p></div>");
	}
	else if (gold >= 100) {
	printf("<p>CONGRATULATIONS YOU'VE REACHED 100 GOLD AND WON!!<p></div>");
	}
	else if (mana == 0 ) {
	printf("<p>I'm sorry but you have died in the dungeon</p></div>");
	}
	else if (strcmp(command, "PLAY") == 0 || strcmp(command, "RIDDLE") == 0) { 
	printf("<p>I'm always there, some distance away. Somewhere between land or sea and sky I lay. You may move towards me, yet distant I stay.(type RIDDLE for the riddle to be redisplayed)</p></div>");
	}
	else if (!strcmp(command, "HORIZON")== 0 && inplay == 0) {
	printf("<p>Sorry you have entered the wrong answer</p></div>");
	}
	else if (invalid == 0) {
	printf("<p>Sorry that is an invalid command</p></div>");
	}
	else if (strcmp(command, "HORIZON") == 0 && inplay == 2) {
	printf("<p>CONGRATULATIONS YOU SOLVED IT<br />The next value you enter will give you that much gold and the mana will be automatically calculated. There is currently %d gold and %d mana in this room</p></div>",roomGold,roomMana); 
	}
	else if (strcmp(command, "QUIT") == 0) {
	printf("<p>You can type PLAY again if you want to continue trying or teleport</p></div>");
	}
	else if (badValue == 0) {
	printf("<p>Don't try to cheat the system. 5 gold max. Thank you<p></div>");
	}
	else if (badValue == 1) {
	printf("<p>Sorry the room does not have enough mana or gold to give you your reward sorry. The room has %d gold and %d mana. You can try again if the room has the ressources</p></div>",roomGold,roomMana);
	}
	else if (strcmp(command, "DROP") == 0) {
	printf("<p>Your gold has been dropped and mana has been given</p></div>");
	}
	else if (strcmp(command, "REFRESH")== 0) {
		if (inplay == 1)
		printf("<p>Hello and Welcome to YouGotToThink. This room is pretty simple, all that must be done is solve a riddle. Type PLAY to begin and then type your answer (in all caps) until you get it right</p></div>");
		else if (inplay == 0)
		printf("<p>I'm always there, some distance away. Somewhere between land or sea and sky I lay. You may move towards me, yet distant I stay.(type RIDDLE for the riddle to be redisplayed)</p></div>");
		else if (inplay == 2)
		printf("<p>CONGRATULATIONS YOU SOLVED IT<br />The next value you enter will give you that much gold and the mana will be automatically calculated. There is currently %d gold and %d mana in this room</p></div>",roomGold,roomMana);
		else if (inplay == 3)
		printf("<p>Your reward has been given. Please move to the next room when you are ready<p></div>");
	}
	else {
	printf("<p>Your reward has been given. Please move to the next room when you are ready<p></div>");
	}
	printf("</div>");
	printf("<div class=\"play\">");
	printf("<div class=\"topRow\">");
	// Display north if not in play
	if (inplay != 0 && inplay != 4) {
	printf("<form name=\"north\" action=\"transporter.py\" method=\"get\">");
	printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\" id=\"inv\">",gold,mana);
	printf("<input type=\"hidden\" name=\"url\" value=\"http://cs.mcgill.ca/~bkuzak1/cgi-bin/playGame.cgi\">");
	printf("<input type=\"submit\" value=\"GO NORTH\"><br />");
	printf("</form>");
	} else { //So the page stays pretty
	printf("<br />");
	}
	printf("</div>");	
	printf("<div class=\"midRow\">");
	printf("<div class=\"west\">");
	//Display west if not in play
	if (inplay != 0 && inplay != 4) {
	printf("<form name=\"west\" action=\"transporter.py\" method=\"get\">");
	printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\" id=\"inv\">",gold,mana);
	printf("<input type=\"hidden\" name=\"url\" value=\"http://cs.mcgill.ca/~bkuzak1/cgi-bin/playGame.cgi\">");
	printf("<input type=\"submit\" value=\"GO WEST\"><br />");
	printf("</form>");
	}
	else {// So the page stays pretty
	printf("<br />");
	}
	printf("</div>");
	printf("<div class=\"inputBox\">");
	//Display command box if not beaten yet
	if (inplay != 3 && inplay != 4) {
	printf("<form name=\"input\" action=\"playGame.cgi\" method=\"get\">");
	printf("<b>Type command:</b><br /><input type=\"text\" name=\"command\"><br />");
	printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\" id=\"inv\">",gold,mana);
	printf("<input type=\"hidden\" name=\"inplay\" value=\"%d\">",inplay);
	printf("<input type=\"submit\" value=\"Enter command\">");
	printf("</form>");
	}
	else {
	printf("<br /><br />"); //So the page stays pretty
	}	
	printf("<div class=\"botRow\">");
	// Display south if not in play
	if (inplay != 0 && inplay != 4) {
	printf("<form name=\"south\" action=\"transporter.py\" method=\"get\">");
	printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\" id=\"inv\">",gold,mana);
	printf("<input type=\"hidden\" name=\"url\" value=\"http://cs.mcgill.ca/~bkuzak1/cgi-bin/playGame.cgi\">");
	printf("<input type=\"submit\" value=\"GO SOUTH\"><br />");
	printf("</form>");
	}
	printf("</div>");
	printf("</div>");
	printf("<div class=\"east\">");
	//Display east if not in play
	if (inplay != 0 && inplay != 4) {
	printf("<form name=\"east\" action=\"transporter.py\" method=\"get\">");
	printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\" id=\"inv\">",gold,mana);
	printf("<input type=\"hidden\" name=\"url\" value=\"http://cs.mcgill.ca/~bkuzak1/cgi-bin/playGame.cgi\">");
	printf("<input type=\"submit\" value=\"GO EAST\"><br />");
	printf("</form>");
	}
	printf("</div>");
	printf("<body></body></html>");
	fputs(overwrite, newRessources);
	fflush(newRessources);
	fclose(newRessources);
	return 0;
}
