#include "answer03.h"
#include <string.h>

char * strcat_ex( char * * dest, int * n, const char * src )
{
	// dest = Destination
	// src = source 
	// n = address of location which stores the value of num of characters that can be stored in *dest
		
	// Append C string src to end of dest

	char * buffer; //	To store cat string

	if ( ( ( * dest ) == NULL ) || ( strlen ( *dest ) + strlen ( src ) > *n ) )
	{
		buffer = malloc ( 1 + 2 * ( strlen ( *dest ) + strlen ( src ) ) );
		*n = ( 1 + 2 * ( strlen ( *dest ) + strlen ( src ) ) );

		strcpy ( buffer, *dest );
		free ( *dest ) ;
		*dest = buffer;
	}

	strcat ( *dest, src );

	return *dest;
}

char * * explode ( const char * str, const char * delims, int * arrLen )
{
	// Takes a string and spitls it into an array of strings using '\0'
	
	char * * retArray;	//	The final return array of eploded strings
	int lastDelim;		// 	To store index of last + 1 delim
	int numDelims = 0;  //  To store the number of delims in str
	int i = 0;			//	Index to go through loops

	// Finding number of delims in str

	while ( str[i] != '\0' )
	{
		if ( strchr ( delims, str[i] ) != NULL )
		{
			numDelims++;
			lastDelim = i+1; 
		}

		i++;
	}

	//	Array length = numDelims + 1
	* arrLen = numDelims + 1;

	return NULL;
}

char * implode ( char ** strArr, int len, const char * glue )
{
	// Takes an array of strings and concatenates the elements into a single string
	
	return NULL;
}

void sortStringArray( char ** arrString, int len )
{
	// Takes an array of strings and sorts them alphabetically, ascending

	return NULL;
}

void sortStringCharacters ( char * str )
{
	// Sorts the characters in a string

	return NULL;
}

void destroyStringArray ( char ** strArr, int len )
{
	// Safely frees all memory assiciated with strArr, and then strArr

	return NULL;
}
