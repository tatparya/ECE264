#include <stdio.h>
#include <stdlib.h>
#include <strlib.h>

#include "answer05.h"

static List * Node_construct( char * string )
{
	List * nd = malloc ( sizeof ( List ) );
	nd -> str = strdup( string );
	nd -> next = NULL;
	return nd;
}

List * List_insert( List * head, char * string )
{
	printf ( "insert %s\n", string );
	List * ptr = Node_construct ( string );
	ptr -> next = head;
	return ptr;
} 

int main ( int argv, char * * argc )
{	
	List_insert( "Hey");
	List_insert( "my");
	List_insert( "name");
	List_insert( "is");
	List_insert( "Tatparya");
	List_insert( "Shankar");
	List_insert( "Blaghd");

	return 0;
}