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
	int lastDelim = 0;	// 	To store index of last + 1 delim
	int numDelims = 0;  //  To store the number of delims in str
	int i = 0;			//	Index to go through loops
	int j = 0;			//	Index to incremend through retArr[0] 
	int k = 0;			//	To copy strings from str to retArr
	int l;

	// Finding number of delims in str

	while ( str[i] != '\0' )
	{
		if ( strchr ( delims, str[i] ) != NULL )
		{
			numDelims++;
		}

		i++;
	}

	//	Array length = numDelims + 1
	* arrLen = numDelims + 1;

	//	Allocating memory for Return Array
	retArray = malloc ( ( * arrLen ) * sizeof ( char * ) );  

	//	Going through str, check for delim and copy 
	for ( i = 0; str[i] != '\0'; i++ )
	{
		if ( strchr ( delims, str[i] ) != NULL )
		{
			// Copy from str to retArr
			retArray[j] =  malloc ( ( i - lastDelim + 1 ) * sizeof ( char ) );

				
			for ( l = 0 ; lastDelim < i; lastDelim++, l++ )
			{
				retArray[j][l] = str[lastDelim];
			}
			retArray[j][l] = '\0';

			lastDelim = i + 1;

			j++;
			
		}
	}
	
	//	Copying the last array
	retArray[j] = malloc ( ( i - lastDelim + 1 ) * sizeof ( char ) );
	for ( l = 0; lastDelim < i; lastDelim++, l++ )
	 {
		retArray[j][l] = str[lastDelim];
	 }
	 retArray[j][l] = '\0';

	// DONE

	return retArray;
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
