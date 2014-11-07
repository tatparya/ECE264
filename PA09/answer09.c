#include <stdio.h>
#include <stdlib.h>

#include "answer09.h"

#define BUFFER 2048

/*
	Used explode function to parse the .tsv file
*/
char * * explode ( const char *, const char *, int * );

/*
 * Construct one BusinessNode. 
*/
BusinessNode * create_node(char * stars, char * name, char * address)
{
	BusinessNode * node = NULL;
	node = malloc( sizeof(BusinessNode) );
	node -> left = NULL;
	node -> right = NULL;
	node -> name = strdup ( name );
	node -> stars = strdup ( stars );
	node -> address = strdup ( address );
	return tn;
}


/* Insert a node into a BST. Primarily used in load_tree_from_file(). Return a
 * pointer to the root of the BST.
 */
BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{

}

/* Parse a .tsv file line by line, create a BusinessNode for each entry, and
 * enter that node into a new BST. Return a pointer to the root of the BST.
 *
 * The explode(...) function from PA03 may be useful for breaking up a lines 
 * into seperate fields. 
 */
BusinessNode * load_tree_from_file(char * filename)
{
	BusinessNode * root;			//	The return value

	char str[BUFFER];				//	Buffer to store string from file
	int length = 0;					//	To store num of exploded strings
	char * * explodedStr = NULL;	//	To store the exploded string
	int i = 0;		//	Iterate through loop to read from file
	int j = 0;		//	Iterate through loop to read exploded string

	FILE * fptr = NULL;				// 	File pointer
	fptr = fopen( "yelp_businesses.tsv", "r");
	if ( fptr == NULL )
	{
		fprintf ( stderr, "Failed to open file" );
		return NULL;
	}

	//	Opened the file read and create tree
	while ( i < 2 )
	{
		j = 0;
		fgets ( str, 2000, fptr );		//	Read the file from file and store in str
		explodedStr = explode ( str, "\t\n", &length );	//	Explode str to parse strings
		/*	
			Got all the strings here
			explodedStr[0] =	rating
			explodedStr[1] =	name
			explodedStr[3] =	address
		*/
		create_node ( explodedStr[0], explodedStr[1], explodedStr[2] );
		i++;
	}

	return root;
}

/* Search a BusinessNode BST for the node with the name 'name'. Returns
 * pointer to the node with a match.
 *
 * If there is no match, return NULL.
 */
BusinessNode * tree_search_name(char * name, BusinessNode * root)
{

}

/* Print out a single node: name, address, and stars
 * The format can be similar to this:
 *
 * Country Cafe
 * ============
 * Stars:
 *    3.5
 * Address:
 *    1030 Emerald Ter, Sun Prairie, WI 53590
 *
 * This function is not graded, but it could come in very handful while
 * debugging this assignment.
 */
void print_node(BusinessNode * node)
{

}


/* Print the entire tree, starting from the root. Like the print_node(...)
 * function, this is not graded.
 */
void print_tree(BusinessNode * node)
{
	printf ( "Rating = %s\n", node -> stars );
	printf ( "Name = %s\n", node -> name );
	printf ( "Address = %s\n", node -> address );
}


/* Deallocate all of the memory used by a BusinessNode BST, without memory
 * leaks.
 */
void destroy_tree(BusinessNode * root)
{
	
}


//	Explode used to parse the tsv file
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
