#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ( int argc, char ** argv )
{
	
	int help = 0;					// To trigger help switch	
	int index;						// Index to go through loops
	
	//	Check for argv[1] present

	// Check for help switch	
	for ( index = 1; index < argc; index++ )	//	Index = 1 because we want to skip the first string
	{
		if ( strcmp ( argv[index], "--help" ) )
		{
			help++;
		}
	}

	if ( help )
	{
		//		PRINT HELP MESSAGE
		printf("Usage: cat-lite [--help] [FILE]...\n"
		"With no FILE, or when FILE is -, read standard input.\n"
		"\n"
		"Examples:\n"
		"  cat-lite README   Print the file README to standard output.\n"
		"  cat-lite f - g    Print f's contents, then standard input,\n"
		"                    then g's contents.\n"
		"  cat-lite          Copy standard input to standard output.\n"
		);
		
		//		EXIT so that program does not read anything else
		return EXIT_SUCCESS;
	}

	else
	{
		//		OPEN FILES AND PRINT CONTENT TO STDOUT

	}

	return EXIT_SUCCESS;
}
