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
	node -> name = name ;
	node -> stars = stars ;
	node -> address = address ;
	return node;
}


/* Insert a node into a BST. Primarily used in load_tree_from_file(). Return a
 * pointer to the root of the BST.
 */
BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
	if ( node == NULL )
	{
		//	fprintf(stderr, "Empty node inserted\n" );
		return NULL;
	}
	if ( root == NULL )
	{
		//	fprintf(stderr, "Root cannot be null\n" );
		return node;
	}
	//	printf("Name = %s\n", root -> name );
	//	printf("Inserting name = %s\n", node -> name );
	//	If nodename less than euql to root name, insert into root -> left
	if ( strcmp ( node -> name, root -> name ) <= 0 )
	{
		//	printf( "Got name = %s which is less than root name = %s, Insert into left\n", node -> name, root -> name );
		if ( root -> left == NULL )
		{
			root -> left = node;
		}
		else 
		{
			root -> left = tree_insert ( node, root -> left );
		}
		
	}

	else
	{
		//	printf( "Got name = %s which is greater than root name = %s, Insert into right\n", node -> name, root -> name );
		if ( root -> right == NULL )
		{
			root -> right = node;
		}
		else 
		{
			root -> right = tree_insert ( node, root -> right );
		}
	}

	return root;
}

/* Parse a .tsv file line by line, create a BusinessNode for each entry, and
 * enter that node into a new BST. Return a pointer to the root of the BST.
 *
 * The explode(...) function from PA03 may be useful for breaking up a lines 
 * into seperate fields. 
 */
BusinessNode * load_tree_from_file(char * filename)
{
	BusinessNode * root;			//	The return value for root
	BusinessNode * node;			//	Return while populating tree
	char str[BUFFER];				//	Buffer to store string from file
	int length = 0;					//	To store num of exploded strings
	char * * explodedStr = NULL;	//	To store the exploded string
	//int i = 0;		//	Iterate through loop to read from file
	int j = 0;			//	Iterate through loop to free exploded string

	FILE * fptr = NULL;				// 	File pointer
	fptr = fopen( filename, "r");
	if ( fptr == NULL )
	{
		fprintf ( stderr, "Failed to open file\n" );
		return NULL;
	}

	//	CREATING THE ROOT
	fgets ( str, 2000, fptr );
	explodedStr = explode ( str, "\t\n", &length );	//	Explode str to parse
	root = create_node ( strdup( explodedStr[0] ), strdup( explodedStr[1] ), strdup( explodedStr[2] ) );	// Creating the root

	//	Free exploded array
	for ( j=0; j < length; j++ )
	{
		free ( explodedStr[j] );
	}
	free ( explodedStr );

	//	READ FILE and POPULATE TREE
	while ( !feof ( fptr )  )
	{
		fgets ( str, 2000, fptr );		//	Read the data from file and store in str
		explodedStr = explode ( str, "\t\n", &length );	//	Explode str to parse strings
		/*	
			Got all the strings here
			explodedStr[0] =	rating
			explodedStr[1] =	name
			explodedStr[3] =	address
		*/
		//	CREATE NODE
		node = create_node ( strdup( explodedStr[0] ), strdup( explodedStr[1] ), strdup( explodedStr[2] ) );

		//	Free exploded array
		for ( j=0; j < length; j++ )
		{
			free ( explodedStr[j] );
		}
		free ( explodedStr );
		//	INSERT NODE INTO TREE
		tree_insert( node, root );
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
	//	printf ( "Searching value %s\n", name );
	//	printf ( "Root name =  %s\n", root -> name );
	//	If not found
	if ( root == NULL )
	{
		printf("Node not found\n");
		return root;
	}

	//	If found
	if ( strcmp ( name, root -> name ) == 0 )
	{
		//	printf("Node with name = %s found\n", root -> name );
		return root;
	}

	//	If search val is less, go into left branch
	if ( strcmp ( name, root -> name ) < 0 )
	{
		//	printf("Root name = %s is greater than node name = %s going into left branch\n", root -> name, name);
		root = tree_search_name ( name, root -> left );
	}

	//	If search val is greater, go into right branch
	else if ( strcmp ( name, root -> name ) > 0 )
	{
		//	printf("Root name = %s is less than node name = %s going into right branch\n", root -> name, name);
		root = tree_search_name ( name, root -> right);
	}

	return root;
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
	printf ( "Stars :\n\t%s\n", node -> stars );
	printf ( "Name :\n\t%s\n", node -> name );
	printf ( "Address : \n\t%s\n", node -> address );
	printf("\n");
}


/* Print the entire tree, starting from the root. Like the print_node(...)
 * function, this is not graded.
 */
void print_tree(BusinessNode * node)
{
	if ( node == NULL )
	{
		//	BASE CASE
		return;
	}

	//	RECURSIVE CASE
	print_tree ( node -> left );
	print_node ( node );
	print_tree ( node -> right );
}


/* Deallocate all of the memory used by a BusinessNode BST, without memory
 * leaks.
 */
void destroy_tree(BusinessNode * root)
{
	if ( root != NULL )
	{
		//	Free left
		if ( root -> left != NULL )
		{
			destroy_tree ( root -> left );
		}
		//	Free right
		if ( root -> right != NULL )
		{
			destroy_tree ( root -> right );
		}
		//	Free stars
		if ( root -> stars != NULL )
		{
			free ( root -> stars );
		}
		//	Free name
		if ( root -> name != NULL )
		{
			free ( root -> name );
		}
		//	Free address
		if ( root -> address != NULL )
		{
			free ( root -> address );
		}
		//	Free root
		free ( root );
	}
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
