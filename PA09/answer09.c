#include <stdio.h>
#include <stdlib.h>

#include "answer09.h"

/*
 * Construct one BusinessNode. 
*/
BusinessNode * create_node(char * stars, char * name, char * address)
{

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
void print_tree(BusinessNode * tree)
{

}


/* Deallocate all of the memory used by a BusinessNode BST, without memory
 * leaks.
 */
void destroy_tree(BusinessNode * root)
{
	
}

