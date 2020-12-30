#include <stdio.h>
#include <string.h>	//for memset
 
int main(void) {
	char cmd[255];
	memset(cmd, 0, 255);
	do
	{
		// read
		fgets(cmd, 255, stdin);
		cmd[strcspn ( cmd, "\n")] = '\0';

		// TODO: do some stuff
		if(!strcmp(cmd, "start"))
			printf("Starting the game.\n");
 
	} while(!strcmp(cmd, "eixt"));	// do until cmd does not equal exit
	printf("Exiting the command line.");
	return 0;
}