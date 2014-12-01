#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

#define BUFFER 10240

/*
	Used explode function to parse the .tsv file
*/
char * * explode ( const char *, const char *, int * );
char * * getlocation ( int offset, const char * filename, int * length );	//	TO RETRIEVE THE ENTIRE LINE GIVEN OFFEST
char * getState( int offset, const char * filename );		//	TO GET THE STATE
char * getCity( int offset, const char * filename );		//	TO GET THE CITY
char * getAddress( int offset, const char * filename );		//	TO GET THE ADDRESS
char * getName( int offset, const char * filename );		//	TO GET THE BUSINESS NAME
char * getID( int offset, const char * filename );			//	TO GET THE BUSINESS ID

/*--------		Structures definitions			-----------*/

typedef struct Review_tree {
	
	int offset;						//	Stroes offset in reviews.tsv
	char * id;						//	Store id
	struct Review_tree * left;		//	Left branch
	struct Review_tree * right;		//	Right branch

}	RevTree;

typedef struct Location_tree {
	
	char * id;						//	Stores business id
	int offset;						//	Stores offset in business.tsv
	char * name;					//	Stores business name
	int numReviews;					//	Number of reviews for the location
	struct Review * revHead;		//	Stores reviews
	struct Location_tree * left;			//	Left Location_tree
	struct Location_tree * right;		//	Right Location_tree

}	LocTree;

typedef struct Business_tree {

	char * name;					//	Stores business name
	struct Location_tree * locRoot;		//	Stores the location linked list
	struct Business_tree * right;	
	struct Business_tree * left;

} 	BusTree;

struct YelpDataBST	{

	struct Business_tree * busRoot;	//	To hold the tree

};

/*---------------------------------------------------------*/

/*----------------------Custom functions-------------------*/

/*----------------------Review tree functions-------------------*/

/*
RevTree * Review_tree_create ( const char * id, int offset, const char * reviews_path, 
							   const char * businesses_path )
{
	RevTree * root;
	root = malloc ( sizeof ( RevTree ) );
	root -> name = strdup ( busName );
	root -> left = NULL;
	root -> right = NULL;
	root -> locRoot = NULL;
	root -> locRoot = Location_tree_insert( root -> locRoot, busName, id, offset, reviews_path, businesses_path );

	return root;
}

RevTree * Review_tree_insert ( RevTree * root, const char * id, int offset, const char * reviews_path, 
							   const char * businesses_path )
{
	if ( root == NULL )
	{
		root = Review_tree_create ( busName, id, offset, reviews_path, businesses_path );
		return root;
	}

	int result;		//	To compare names and insert node into branches
	result = strcmp ( root -> name, busName );
	if ( result < 0 )
	{
		//	Insert into left
		root -> left = Review_tree_insert ( root -> left, busName, id, offset, reviews_path, businesses_path );
	}
	else if ( result > 0 )
	{
		//	Insert into right
		root -> right = Review_tree_insert ( root -> right, busName, id, offset, reviews_path, businesses_path );
	}
	else	//	New location for a business already in memory, INSERT to Location_tree Tree
	{
		//	Insert into LocTree
		root -> locRoot = Location_tree_insert ( root -> locRoot, busName, id, offset, reviews_path, businesses_path );
	}

	return root;
}

void Review_tree_destroy ( RevTree * root )
{
	if ( root == NULL )
	{
		return;
	}

	Review_tree_destroy ( root -> left );
	Review_tree_destroy ( root -> right );

	free ( root -> id );
	free ( root );
}
*/

//					LOCATION TREE FUNCTIONS

LocTree * Location_tree_create ( const char * busName, const char * id, int offset, 
				const char * reviews_path, const char * businesses_path )
{
	LocTree * root;
	root = malloc ( sizeof ( LocTree ) );
	root -> name = strdup ( busName );
	root -> id = strdup ( id );
	root -> offset = offset;
	root -> numReviews = 0;		//		** CALCULATE NUM REVIEWS
	root -> revHead = NULL;		//		**	TODO Create reviews tree
	root -> left = NULL;
	root -> right = NULL;

	return root;
}

LocTree * Location_tree_insert ( LocTree * root, const char * busName, const char * id, int offset, 
				const char * reviews_path, const char * businesses_path )
{
	//	CREATING NEW NODE
	if ( root == NULL )
	{
		root = Location_tree_create ( busName, id, offset, reviews_path, businesses_path );
		return root;
	}

	//	INSERT NODE INTO LEFT OR RIGH
	char * rootState = getState ( root -> offset, businesses_path );
	char * nodeState = getState ( offset, businesses_path );
	char * rootCity = getCity ( root -> offset, businesses_path );
	char * nodeCity = getCity ( offset, businesses_path );
	char * rootAddress = getAddress ( root -> offset, businesses_path );	
	char * nodeAddress = getAddress ( offset, businesses_path );
	int result1 = strcmp ( rootState, nodeState );
	int result2 = strcmp ( rootCity, nodeCity );
	int result3 = strcmp ( rootAddress, nodeAddress );

	free ( rootState );
	free ( nodeState );
	free ( rootCity );
	free ( nodeCity );
	free ( rootAddress );
	free ( nodeAddress );

	if ( result1 < 0 )
	{
		//	Insert into left
		root -> left = Location_tree_insert( root -> left, busName, id, offset, reviews_path, businesses_path );
	}
	else if ( result1 > 0 )
	{
		//	Insert into right
		root -> right = Location_tree_insert( root -> right, busName, id, offset, reviews_path, businesses_path );
	}
	else if ( result2 < 0 )
	{
		//	Insert into left
		root -> left = Location_tree_insert( root -> left, busName, id, offset, reviews_path, businesses_path );
	}
	else if ( result2 > 0 )
	{
		//	Insert into right
		root -> right = Location_tree_insert( root -> right, busName, id, offset, reviews_path, businesses_path );
	}
	else if ( result3 < 0 )
	{
		//	Insert into left
		root -> left = Location_tree_insert( root -> left, busName, id, offset, reviews_path, businesses_path );
	}
	else
	{
		//	Insert into right
		root -> right = Location_tree_insert( root -> right, busName, id, offset, reviews_path, businesses_path );
	}

	return root;
}

void Location_tree_destroy ( LocTree * root )
{
	if ( root == NULL )
	{
		return;
	}

	Location_tree_destroy ( root -> left );
	Location_tree_destroy ( root -> right );
	// TODO Review_tree_destroy ( locRoot );

	free ( root -> name );
	free ( root -> id );
	free ( root );
}

//				BUSINESS TREE FUNCTIONS

BusTree * Business_tree_create ( const char * busName, const char * id, int offset, 
				const char * reviews_path, const char * businesses_path )
{
	BusTree * root;
	root = malloc ( sizeof ( BusTree ) );
	root -> name = strdup ( busName );
	root -> left = NULL;
	root -> right = NULL;
	root -> locRoot = NULL;
	root -> locRoot = Location_tree_insert( root -> locRoot, busName, id, offset, reviews_path, businesses_path );

	return root;
}

BusTree * Business_tree_insert ( BusTree * root, const char * busName, const char * id, int offset,
				const char * reviews_path, const char * businesses_path )
{
	if ( root == NULL )
	{
		root = Business_tree_create ( busName, id, offset, reviews_path, businesses_path );
		return root;
	}

	int result;		//	To compare names and insert node into branches
	result = strcmp ( root -> name, busName );
	if ( result < 0 )
	{
		//	Insert into left
		root -> left = Business_tree_insert ( root -> left, busName, id, offset, reviews_path, businesses_path );
	}
	else if ( result > 0 )
	{
		//	Insert into right
		root -> right = Business_tree_insert ( root -> right, busName, id, offset, reviews_path, businesses_path );
	}
	else	//	New location for a business already in memory, INSERT to Location_tree Tree
	{
		//	Insert into LocTree
		root -> locRoot = Location_tree_insert ( root -> locRoot, busName, id, offset, reviews_path, businesses_path );
	}

	return root;
}

void Business_tree_destroy ( BusTree * root )
{
	if ( root == NULL )
	{
		return;
	}

	Business_tree_destroy ( root -> left );
	Business_tree_destroy ( root -> right );
	Location_tree_destroy ( root -> locRoot );

	free ( root -> name );
	free ( root );
}

/*---------------------------------------------------------*/

/*----------------------Functions from answer.h-----------------------*/

/* This function reads the two files and creates an index that can be used
 * to search the data and quickly retrieve the reviews. */
struct YelpDataBST* create_business_bst(const char* businesses_path,
                                        const char* reviews_path)
{
	struct YelpDataBST * yelpTree;
	yelpTree = malloc ( sizeof ( struct YelpDataBST ) );
	FILE * fptr;
	fptr = fopen ( businesses_path, "r" );
	char * busName;
	char * id;
	char str[BUFFER];
	int offset;

	if ( fptr == NULL )
	{
		fprintf ( stderr, "File %s could not be open.\n", businesses_path );
		return NULL;
	}

	while ( !feof( fptr ) )
	{
		offset = ftell( fptr );
		busName = getName( offset, businesses_path );
		id = getID( offset, businesses_path );
		fgets ( str, BUFFER, fptr );

		yelpTree -> busRoot = Business_tree_insert ( yelpTree -> busRoot, busName, id, offset, reviews_path, businesses_path );


		free ( busName );
		free ( id );
	}

	fclose ( fptr );
	
	return yelpTree;
}

/* get_business_reviews(...) should return a pointer to a Business struct object
 * on the heap.	*/
struct Business* get_business_reviews(struct YelpDataBST* bst,
                                      char* name, char* state, char* zip_code)
{

	return NULL;
}


/* Deallocate all memory allocated for the object returned by
 * create_business_bst(..) and close the files. */
void destroy_business_bst(struct YelpDataBST* bst)
{

	Business_tree_destroy ( bst -> busRoot );
	free ( bst );

}

/* Deallocate all heap memory tied to an object returned by
 * get_business_reviews(..). */
void destroy_business_result(struct Business* b)
{



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

char * * getlocation ( int offset, const char * filename, int * length )
{
	char str[BUFFER];
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

	explodedStr = explode ( str, "\t\n", length );

	fclose ( fptr );

	return explodedStr;
}

char * getState( int offset, const char * filename )
{
	int length = 0;
	char * * explodedStr = getlocation ( offset, filename, &length );
	char * state;
	
	state = strdup ( explodedStr[4] );
	
	int itr = 0;
	while ( length > 0 )
	{
		free ( explodedStr[itr] );
		length--;
		itr++;
	}
	free ( explodedStr );

	return state;
}

char * getCity( int offset, const char * filename )
{
	int length = 0;
	char * * explodedStr = getlocation ( offset, filename, &length );
	char * city;

	city = strdup ( explodedStr[3] );
	 
	int itr = 0;
	while ( length > 0 )
	{
		free ( explodedStr[itr] );
		length--;
		itr++;
	}
	free ( explodedStr );

	return city;
}

char * getAddress( int offset, const char * filename )
{
	int length = 0;
	char * * explodedStr = getlocation ( offset, filename, &length );
	char * address;

	address = strdup ( explodedStr[2] );
	
	int itr = 0;
	while ( length > 0 )
	{
		free ( explodedStr[itr] );
		length--;
		itr++;
	}
	free ( explodedStr );

	return address;
}

char * getName( int offset, const char * filename )
{
	int length = 0;
	char * * explodedStr = getlocation ( offset, filename, &length );
	char * busName;

	busName = strdup ( explodedStr[1] );
	
	int itr = 0;
	while ( length > 0 )
	{
		free ( explodedStr[itr] );
		length--;
		itr++;
	}
	free ( explodedStr );

	return busName;
}

char * getID( int offset, const char * filename )
{
	int length = 0;
	char * * explodedStr = getlocation ( offset, filename, &length );
	char * id;

	id = strdup ( explodedStr[0] );
	
	int itr = 0;
	while ( length > 0 )
	{
		free ( explodedStr[itr] );
		length--;
		itr++;
	}
	free ( explodedStr );

	return id;
}