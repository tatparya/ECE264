#include <stdio.h>
#include <stdlib.h>

#include "answer09.h"

typedef struct treeNode
{
	/* data */
	int value;

	struct treeNode * left;
	struct treeNode * right;

} TreeNode;

TreeNode * nodeConstruct ( int val )
{
	TreeNode * tn = NULL;
	tn = malloc( sizeof(TreeNode) );
	tn -> left = NULL;
	tn -> right = NULL;
	tn -> value = val;
	return tn;
}

TreeNode * treeInsert ( TreeNode * tn, int val )
{
	if ( tn == NULL )
	{
		//	empty, create node
		return nodeConstruct( val );
	}

	printf("val = %d\n", val );
	if ( val < ( tn -> value ))
	{
		tn -> left = treeInsert ( tn -> left, val );
		printf( "Got val less than %d\n", tn -> value );
	}

	else if ( val > ( tn -> value ))
	{
		tn -> right = treeInsert ( tn -> right, val );
		printf( "Got val greater than %d\n", tn -> value );
	}

	else
	{
		//	do not insert value, values must be distinct
		fprintf ( stderr, "Values must be distinct" );
	}

	return tn;
}

//	Search for node with specific value
void searchNode ( TreeNode * node, int val ) 
{
	printf ( "Searching value %d\n", val );

	if ( node == NULL )
	{
		printf("Node not found\n");
		return;
	}

	if ( ( node -> value ) == val )
	{
		printf("Node with value = %d found\n", node -> value );
		return;
	}

	if ( val < ( node -> value ) )
	{
		printf("Node value = %d is greater than val going into left branch\n", node -> value );
		searchNode ( node -> left, val );
	}

	else if ( val > ( node -> value ) )
	{
		printf("Node value = %d is less than val going into right branch\n", node -> value );
		searchNode ( node -> right, val );
	}
}

void printNode ( TreeNode * tn )
{
	printf ( "%d\n", tn -> value );
}

void treePrint( TreeNode * tn )
{
	if ( tn == NULL )
	{
		//	BASE CASE
		return;
	}

	//	RECURSIVE CASE
	treePrint ( tn -> left );
	printNode ( tn );
	treePrint ( tn -> right );
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

int main()
{
	/*
	int i=0;
	int j;
	int rootval = 5;
	TreeNode * root;
	root = treeInsert ( root, 5 );
	for ( i = 1, j = 20; i < 21; i+=2, j -= 2 )
	{
		if ( i != 5 )
		{
			root = treeInsert ( root, i );
			root = treeInsert ( root, j );
		}
	}
	treePrint ( root );

	searchNode ( root, 8 );
	return 0;
	*/

	char * rating;
	char * name;
	char * address;
	char str[2000];
	int length = 0;
	char * * explodedStr = NULL;

	FILE * fptr = NULL;
	fptr = fopen( "yelp_businesses.tsv", "r");

	if ( fptr == NULL )
	{
		fprintf ( stderr, "Failed to open file" );
	}
	int i = 0;
	int j = 0;
	printf("\n\n");
	while ( i < 2 )
	{
		j = 0;
		//fgets ( tempstr, 100, fptr );
		fgets ( str, 2000, fptr );
		explodedStr = explode ( str, "\t\n", &length );
		//	Got all the strings here
		while ( j < length )
		{
			printf("%s Len = %d\n", explodedStr[j], (int)strlen( explodedStr[j] ));
			j++;
		}
		printf ( "%s\n", str );
		i++;
	}

	return 0;
}