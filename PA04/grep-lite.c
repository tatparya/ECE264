#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 2000

int main ( int argc, char ** argv )
{
	//Check for --help trigger
	int help = 0;                   // To trigger help switch   
    int index;                      // Index to go through loops

	//			Defining all switched
	int invert = 0;
	int line = 0;
	int quiet = 0;
	int found = 0;

	//  Check for argv[1] present
  
    // Check for help switch    
    
	for ( index = 1; index < argc; index++ )    //  Index = 1 because we want to skip the first string
    {
        if ( strcmp ( argv[index], "--help" ) == 0 )
        {
            help++;
		}
	}

	if ( !help )
	{
		//          TO CHECK IF LAST ARGV IS A PATTERN AND NOT A TRIGGER
		if ( argc > 1 && argv[argc-1][0]  == '-' )
		{
		//      Last argument is not a pattern, rerturn 2
			fprintf ( stderr, "'%s' is not a valid Pattern", argv[argc-1] );
			return 2;
		}

	}
	if ( help )
	{
		//	PRINT HELP MESSAGE
		printf("Usage: grep-lite [OPTION]... PATTERN\n"
		"Search for PATTERN in standard input. PATTERN is a\n"
		"string. grep-lite will search standard input line by\n"
		"line, and (by default) print out those lines which\n"
		"contain pattern as a substring.\n"
		"\n"
		"  -v, --invert-match     print non-matching lines\n"
		"  -n, --line-number      print line numbers with output\n"
		"  -q, --quiet            suppress all output\n"
		"\n"
		"Exit status is 0 if any line is selected, 1 otherwise;\n"
		"if any error occurs, then the exit status is 2.\n"
		);
	
		return EXIT_SUCCESS;
	}
	
	//		If help trigger is not found
	
	char buffer[MAX];			// To recieve inputs from stdin
	int lineNumber = 1;			// To keep track of line number

	for ( index = 1; index < argc ; index++ )
	{
		//	Add condition to skip stdin
		if ( strcmp ( argv[index], "-v" ) == 0 )
		{
			//		INVERT MATCH
			invert++;
		}
		else if ( strcmp ( argv[index], "-n" ) == 0 )
		{
			//		LINE NUMBER
			line++;
		}

		else if ( strcmp ( argv[index], "-q" ) == 0 )
		{
			//		QUIET
			quiet++;
			return EXIT_SUCCESS;
		}
		else
		{
			//		BOGUS Argument
			fprintf ( stderr, "Unknown switch '%s'\n", argv[index] );
			return 2;
		}
	}

	while ( fgets( buffer, MAX, stdin ) != NULL )
	{
		strcpy ( buffer, "");
		if ( strstr ( buffer, argv[ argc - 1 ] ) != NULL )
		{
			//		Pattern found in stdin
			found++;
			if ( line )
			{
				printf("%d:", lineNumber );
			}
			printf("%s\n", buffer );
		}

		else
		{
			//		Pattern not present in line
			if ( invert )
			{
				printf("%s\n", buffer );
			}
		}
		
		lineNumber++;
	}
	return EXIT_SUCCESS;
}
