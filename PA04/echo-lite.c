#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * * argv)
{
   	// Loop through the arguments
   	int ind = 1; // skip 0, which is the program path
   	for( ; ind < argc; ++ind)
	{
		// Print to the stdout
		fprintf ( stdout, "%s ", argv[ind] );		
	}

	printf("\n");
	
   return EXIT_SUCCESS;
}
