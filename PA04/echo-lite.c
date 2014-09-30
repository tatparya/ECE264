#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * * argv)
{
   // We want some variables to store which "switches" were set
	int showHelp = FALSE;
	int echo = FALSE;
	int badSwitch = FALSE;

   // Loop through the arguments, looking for our switches...
   	int ind = 1; // we always skip 0, which is the program path
   	for( ; ind < argc; ++ind)
	{
			if ( strcmp(argv[ind], 
			
			printf("%s ", argv[ind] ); 
	}

	printf("\n");
	
   return EXIT_SUCCESS;
}
