#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 2000

void helpMessage();			//	To print Help message
void readStdin();			//	To read from stdin and write to stdout
int readFile( char * );			//	To read from file and write to stdout => RETURNS file open fail / success

int main ( int argc, char ** argv )
{
	
	int help = 0;			// To trigger help switch	
	int index;				// Index to go through loops
	
	//------CHECK FOR NO ARG------
	if ( argc == 1 )		// ( ./cat-lite ) => Printf stdin to stdout
	{
		//	Read from stdin
		readStdin();
		//	EXIT
		return EXIT_SUCCESS;	
	}
	
	//------CHECK FOR HELP SWITCH------
	for ( index = 1; index < argc; index++ )		//	Index = 1 because we want to skip the first string
	{
		if ( strcmp ( argv[index], "--help" ) == 0 )
		{
			help++;
		}
	}

	if ( help )		// If help switch present then, Print help message and return EXIT_SUCCESS
	{
		//	Print Help Message
		helpMessage();
		//	EXIT
		return EXIT_SUCCESS;
	}

	//------OPEN FILES AND PRINT CONTENT TO STDOUT------
	for ( index = 1; index < argc; index++ )	//	To go through all args
	{
		//	argv[index] gives File name
		int fileStatus = 0;			// To check if file opened
		
		//	Check for stdin trigger
		if ( argv[index][0] != '-' )
		{
			//	Read FILE and Write to stdout
			fileStatus = readFile( argv[index] );
			
			if ( fileStatus == 0 )
			{
				// File not opened
				return EXIT_FAILURE;
			}
		}
		else
		{
			//	( cat-lite - ) => Read from stdin and write to stdout
			readStdin();
		}
	}
	
	return EXIT_SUCCESS;
}

void helpMessage()
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
}	

void readStdin()
{
	char buffer;		//	To store read string
	
	//	Read from stdin and write to stdout
	buffer = fgetc ( stdin );
	while ( buffer != EOF )
	{
		fputc( buffer, stdout );
		buffer = fgetc ( stdin );
	}	
}

int readFile( char * filename )
{
	FILE * filePtr;			//	File pointer to find file location
	char buffer;			//	To store read char from file	
	
	//	Open file
	filePtr = fopen( filename, "r" );

	//	Check if file opened successfully		
	if ( filePtr == NULL )
	{
		//	File open failed
		fprintf ( stderr, "cat cannot open %s\n", filename );
		return 0;
	}
	
	//	Read from file
	buffer = fgetc ( filePtr );
	while ( buffer != EOF )
	{
		fputc( buffer, stdout );
		buffer = fgetc ( filePtr );
	}	
	
	//	Close File when done reading
	if ( filePtr != NULL )
	{	
		fclose ( filePtr );
	}
	return 1;
}
