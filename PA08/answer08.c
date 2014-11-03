#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "answer08.h"

/**
 * Create a new list-node with the passed string. 
 * str should be copied (with strdup).
 */
List * List_createNode( const char * str )
{
	List * node = malloc ( sizeof ( List ) );
	node -> str = strdup ( str );
	node -> next = NULL;

	return node;
}

/**
 * Free all memory associated with the linked list, including memory for
 * contained strings. Must safely handle NULL lists.
 */
void List_destroy( List * list )
{
	if ( list == NULL )
	{
		return;
	}
	List_destroy( list -> next );
	free ( list -> str );
	free ( list );
}

/**
 * Length of a linked list. 
 * The length of "NULL" is 0.
 */
int List_length( List * list )
{
	int length;	//	Stores length
	
	if ( list == NULL )
	{
		length = 0;
	}
	else
	{
		length = List_length( list -> next ) + 1;
	}

	return length;
}

/**
 * Merge two sorted lists to produce a final sorted list.
 */
List * List_merge( List * lhs, List * rhs, int (*compar)(const char *, const char*) )
{
	//	Creating a new result list and first and last pointers
	List * first = NULL;
	List * last = NULL;

	//	Comparing nodes and catenating into result list
	while ( lhs != NULL && rhs != NULL )
	{
		int cmpResult = compar( lhs -> str, rhs -> str );

		//	If lhs > rhs
		if ( cmpResult < 0 )
		{
			if ( first == NULL )
			{
				first = lhs;
				last = lhs;
			}
			else 
			{
				last -> next = lhs;
				last = lhs;
			}
			//	Incremend list
			lhs = lhs -> next;
		}
		else
		{
			if ( first == NULL )
			{
				first = rhs;
				last = rhs;
			}
			else
			{
				last -> next = rhs;
				last = rhs;
			}
			//	Incremend list
			rhs = rhs -> next;
		}
		last -> next = NULL;
	}
	//	Only lhs left to be added
	if ( lhs == NULL )
	{
		if ( first == NULL )
		{
			first = rhs;
			return first;
		}
		else
		{
			last -> next = rhs;
		}
	}
	//	Only rhs left to be added
	if ( rhs == NULL )
	{
		if ( first == NULL )
		{
			first = lhs;
			return first;
		}
		else
		{
			last -> next = lhs;
		}
	}

	//	Return list
	return first;
} 


/** 
 * Sorts the list's elements using the merge-sort algorithm.
 */
 List * List_sort( List * list, int (*compar)(const char *, const char*) )
{
	List * leftPart;	//	To store left half of split list
	List * rightPart;	//	To store right part of split list
	List * temp = list;
	int length = List_length ( list );
	int mid;
	//	If list has 0 or 1 element, list is already sorted
	if ( length < 2 )
	{
		return list;
	}

	//	If list has more than 2 elements, Split list
	mid = length / 2;
	leftPart = list;
	while ( mid != 1 )
	{
		temp = temp -> next;
		mid--;
	}

	//	Traversed halfway through list
	rightPart = temp -> next;
	temp -> next = NULL;

	//	Recursive Call to split lists further
	//	Sort Left
	leftPart = List_sort ( leftPart, compar );

	// 	Sort Right
	rightPart = List_sort ( rightPart, compar );

	//	Merge lists
	return List_merge ( leftPart, rightPart, compar );
}
