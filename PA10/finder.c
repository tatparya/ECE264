#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER 10240

char * * explode ( const char * str, const char * delims, int * arrLen );

char * * getlocation ( int offset, char * filename )
{
	char str[BUFFER];
	int length = 0;
	char * * location;	// 0 - State, 1 - City, 2 - Address
	char * * explodedStr = NULL;
	FILE * fptr;
	fptr = fopen ( filename, "r" );
	if ( fptr == NULL )
		{
			printf("File could not be open\n");
			return NULL;
		}
	fseek ( fptr, offset, SEEK_SET );
	fgets ( str, BUFFER, fptr );

	explodedStr = explode ( str, "\t\n", &length );

	fclose ( fptr );

	return explodedStr;
}

int main(int argc, char const *argv[])
{
	char storage[BUFFER];
	char * filename = "dataset/businesses.short.tsv";
	FILE * fptr;
	fptr = fopen ( filename, "r" );
	if ( fptr == NULL )
	{
		printf("File could not be open\n");
		return 0;
	}
	fgets ( storage, BUFFER, fptr );
	fgets ( storage, BUFFER, fptr );
	fgets ( storage, BUFFER, fptr );
	int offset = ftell ( fptr );

	char * * result = getlocation ( offset, filename );

	fclose( fptr );

	return 0;
}

/*	Explode used to parse the tsv files
	                     _             _       
	                    | |           | |      
	   ___ __  __ _ __  | |  ___    __| |  ___ 
	  / _ \\ \/ /| '_ \ | | / _ \  / _` | / _ \
	 |  __/ >  < | |_) || || (_) || (_| ||  __/
	  \___|/_/\_\| .__/ |_| \___/  \__,_| \___|
	             | |                           
	             |_|                           
*/
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