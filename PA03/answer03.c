#include "answer03.h"
#include <string.h>
#include <stdio.h>

char * strcat_ex( char * * dest, int * n, const char * src )
{
	// dest = Destination
	// src = source 
	// n = address of location which stores the value of num of characters that can be stored in *dest
		
	// Append C string src to end of dest

	char * buffer; //	To store cat string

	if ( ( ( * dest ) == NULL ) || ( strlen ( *dest ) + strlen ( src ) > *n ) )
	{
		if ( * dest != NULL && src != NULL )
		{
			buffer = malloc ( 1 + 2 * ( strlen ( *dest ) + strlen ( src ) ) );
			*n = ( 1 + 2 * ( strlen ( *dest ) + strlen ( src ) ) );
		}
		else if ( * dest == NULL )
		{
			buffer = malloc ( 1 + 2 * ( strlen ( src ) ) );
			*n = ( 1 + 2 * strlen ( src ) );			
		}	

		buffer[0] ='\0';

		if ( buffer != NULL && *dest != NULL ) 
		{
			strcpy ( buffer, *dest );
		}

		if ( *dest != NULL )
		{
			free ( *dest );
		}
		
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
	int l;				//	To copy strings from str to retArray

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
	
	char * retStr;			// The final imploded string
	//char * buffer;			// To add str and glue
	int i = 0;
	int retStrLen = 0;		// To calc the len of retStr
	//int bufferLen = 0;		// To copy contents of strArr

	// Added this part to caclulate req size

	for ( i = 0; i < len; i++ )
	{
		if ( strArr[i] != NULL )
		{			
			retStrLen += strlen ( strArr[i] );
		}
	}
	
	retStrLen += strlen ( glue ) * i + 1;
	retStr = malloc ( retStrLen * sizeof ( char ) );
	retStr[0] = '\0';

	for ( i = 0; i < len - 1; i++ )
	{
		if ( i == 0 )
		{
			retStr = strcat_ex ( &retStr, &retStrLen, strArr[i] );
			strcat ( retStr, glue );
		}
		else
		{
			strcat ( retStr, strArr[i]);
			strcat ( retStr, glue );
		}
	}

	strcat ( retStr, strArr[i] );

	/*

	retStr = malloc( sizeof ( char ) );
	retStr[0] = '\0';
	
	for ( i = 0; i < len - 1; i ++ )
	{
		buffer = malloc( sizeof ( char ) );
		buffer[0] = '\0';

		if ( buffer != 0 )
		{
			bufferLen = strlen ( buffer );
		}

		// Copy strArr in buffer
		strcat_ex ( &buffer, &bufferLen, strArr[i] );
		// Add glue after strArr in buffer	
		strcat_ex ( &buffer, &bufferLen, glue );
		
		if ( retStr != NULL )
		{
			retStrLen = strlen ( retStr );
		}

		// catenate buffer to return string
		strcat_ex ( &retStr, &retStrLen, buffer );
		
		// Free buffer every time after done copying to have empty buffer
		free( buffer );

	}

	if ( retStr != NULL )
	{		
		retStrLen = strlen ( retStr );
	}
	strcat_ex ( &retStr, &retStrLen, strArr[i] );

	*/

	return retStr;
}

int compareString ( const void * arg1, const void * arg2 )
{
	int compare;
	
	// Convert
	const char * * ptr1 = ( const char * * ) arg1;
	const char * * ptr2 = ( const char * * ) arg2;

	// Retrieve
	const char * string1 = *ptr1;
	const char * string2 = *ptr2;

	// Compare
	compare = strcmp ( string1, string2 );

	if ( compare > 0 )
	{
		return 1;
	}

	else if ( compare < 0 )
	{
		return -1;
	}

	else 
	{
		return 0;
	}
}

void sortStringArray( char ** arrString, int len )
{
	// Takes an array of strings and sorts them alphabetically, ascending
	qsort ( arrString, len, sizeof( char * ), compareString );

}

int compareChar ( const void * arg1, const void * arg2 )
{
	// Convert
	const char * ptr1 = ( const char * ) arg1;
	const char * ptr2 = ( const char * ) arg2;

	// Retrieve
	const char a = *ptr1;
	const char b = *ptr2;

	// Compare
	if ( ( a - b ) > 0 )
	{
		return 1;
	}
	else if ( ( a - b ) < 0 )
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void sortStringCharacters ( char * str )
{
	// Sorts the characters in a string
	qsort ( str, strlen( str ), sizeof(char), compareChar );
}

void destroyStringArray ( char ** strArr, int len )
{
	// Safely frees all memory assiciated with strArr, and then strArr
		
	int i = 0;

	if ( strArr != NULL )
	{
		for ( i = 0; i < len; i++ )
		{
			free ( strArr[i] );
		}

		free ( strArr );
	}

}
