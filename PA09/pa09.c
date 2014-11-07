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


int main()
{
	FILE * fptr;	//	to hold the file ptr
	char * str = NULL;		//	to hold the read string

	fptr = fopen ( "yelp_businesses.tsv", "r");
	if ( fptr == NULL )
	{
		fprintf(stderr, "File could not be open\n" );
		return 0;
	}

	int i = 0;

	while ( i < 1 )
	{
		fgets ( str, 200, fptr );
		printf("%s\n", str);
		i++;
	}
	return 0;
}