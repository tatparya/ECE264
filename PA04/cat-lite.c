#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 2000

int main ( int argc, char ** argv )
{
	
	int help = 0;					// To trigger help switch	
	int index;						// Index to go through loops
	//	Check for argv[1] present

	// Check for help switch	
	for ( index = 1; index < argc; index++ )	//	Index = 1 because we want to skip the first string
	{
		if ( strcmp ( argv[index], "--help" ) == 0 )
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

	//		OPEN FILES AND PRINT CONTENT TO STDOUT
	for ( index = 1; index < argc; index++ )
	{
		//	argv[index] gives File name

		//	Check for stdin trigger
		if ( argv[index][0] != '-' )
		{
			FILE * filePtr;			// File pointer to find file location
			//	Open file
			filePtr = fopen( argv[index], "r" );

			//	Check if file opened successfully		
			if ( filePtr == NULL )
			{
				//	If file open failed
				fprintf ( stderr, "cat cannot open %s\n", argv[index] );
				return EXIT_FAILURE;
			}
	
			//	Read from file
			char buffer[ MAXSIZE ];
			while ( fscanf ( filePtr, "%s", buffer ) == 1 )
			{
				//		Write to stdout
				printf( "%s", buffer);
			}
	
			printf ( "\n" );						
	
			//	Close File when done reading
			if ( filePtr != NULL )
			{	
				fclose ( filePtr );
			}
		}
		else
		{
			char buffer[ MAXSIZE ];
			
			//	Read from stdin and write to stdout
			while ( fgets ( buffer, MAXSIZE, stdin ) != NULL )
			{
				printf("%s\n", buffer );
			}
		}
	}

	return EXIT_SUCCESS;
}
