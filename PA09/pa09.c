#include <stdio.h>
#include <stdlib.h>

#include "answer09.h"

int main()
{
	BusinessNode * tree;
	tree = load_tree_from_file ( "yelp_businesses.tsv");
	BusinessNode * node = tree_search_name ( "Dusit Restaurant", tree );
	BusinessNode * node2 = create_node( "5.0", "Purdue University Electrical Engineering", "465 Northwestern Avenue" );
	print_node ( node );

	printf("------------ Printing node 2-------------\n\n\n");
	print_node ( node2 );

	printf ( "\n\nThe root of the tree is : \n");
	print_node ( tree );
	printf ( "\n\n");

	printf("------------ Printing tree-------------\n\n\n");
	//print_tree ( tree );
	return 0;
}