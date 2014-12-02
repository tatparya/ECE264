#include <stdlib.h>
#include <stdio.h>
#include "answer11.h"

#define FALSE 0
#define TRUE 1

/**
 * Create a new, properly intialized HuffNode
 */
HuffNode * HuffNode_create(int value)
{
	HuffNode * node;
	node = malloc ( sizeof ( HuffNode ) );
	node -> value = value;
	node -> left = NULL;
	node -> right = NULL;

	return node;
}

/**
 * Destroy a tree, including all sub-children. Must handle NULL values safely.
 */
void HuffNode_destroy(HuffNode * tree)
{
	if ( tree == NULL )
	{
		//	BASE CASE
		return;
	}

	//	RECURSIVE CASE	
	HuffNode_destroy( tree -> left );
	HuffNode_destroy( tree -> right );
	free ( tree );
}

StackNode * StackNode_create( HuffNode * tree )
{
	StackNode * node;
	node = malloc ( sizeof ( StackNode ) );
	node -> tree = tree;
	node -> next = NULL;

	return node;
}

/**
 * Returns a pointer to a new empty stack struct
 */
Stack * Stack_create()
{
	Stack * stack;
	stack = malloc ( sizeof ( Stack ) );
	stack -> head = NULL;

	return stack;
}

/**
 *	Frees all the memory associated with the linked list of
 *	StackNodes
 */
void StackNode_destroy( StackNode * head )
{
	if ( head == NULL )
	{
		return;
	}

	free ( head -> next );
	free ( head );
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you must free the entire contained linked-list.
 * Also, you must safely do nothing if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
	StackNode_destroy ( stack -> head );
	free ( stack );
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
	if ( stack -> head == NULL )
	{
		return TRUE;
	}

	return FALSE;
}

/**
 * Pop the front (top) 'value' (i.e. Huffman tree) from the stack.
 *
 * More precisely, this function must do three things:
 * (1) Save the value (i.e. Huffman tree) of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 * (3) Return the value (i.e. Huffman tree) saved in (1).
 */
HuffNode * Stack_popFront(Stack * stack)
{
	HuffNode * tree;			//	To save the value
	StackNode * newHead;		//	To store new head
	StackNode * oldHead;		//	To remove old head
	newHead = stack -> head;	
	tree = newHead -> tree;		//	Saving the popped value
	oldHead = stack -> head;
	newHead = newHead -> next;
	stack -> head = newHead;	//	Setting stack head to newHead
	oldHead -> next = NULL;		//	Removed old head
	StackNode_destroy ( oldHead );

	return tree;				//	Returned stored value
}

/**
 * Push a 'value' (i.e. Huffman tree) onto the front (top) of the stack.
 *
 * More precisely, this function must do two things:
 * (1) Create a new StackNode with 'tree' for its tree.
 * (2) Push that new StackNode onto the front of the stack's list.
 */
void Stack_pushFront(Stack * stack, HuffNode * tree)
{
	StackNode * node = StackNode_create( tree );
	node -> next = stack -> head;
	stack -> head = node;
}

// -------------------------------------------------------- Pop Pop combine Push

/**
 *	This function takes two stacknodes and combines them
 *	using the Hoffman Algorithm
 */
HuffNode * combineTrees ( HuffNode * root1, HuffNode * root2 )
{
	HuffNode * combinedRoot;
	combinedRoot = HuffNode_create( root1 -> value + root2 -> value );
	combinedRoot -> left = root1;
	combinedRoot -> right = root2; 

	return combinedRoot;
}

/**
 * This function helps simplify building a Huffman Coding Tree from the header
 * information. It takes a stack as input. As a precondition, you can assume 
 * that the stack has at least two nodes. This function pops the front (top) 
 * two nodes, combines them into a single node, and pushes the new node back 
 * onto the stack. See Huffman_Coding.pdf to understand conceptually how this
 * should be done.
 */
void Stack_popPopCombinePush(Stack * stack)
{
	HuffNode * combinedTree;
	HuffNode * root1 = Stack_popFront( stack );
	HuffNode * root2 = Stack_popFront( stack );
	combinedTree = combineTrees( root2, root1 );

	Stack_pushFront( stack, combinedTree );
}
 
// ---------------------------------------------------- Reading HuffTree headers

int numElementsInStack( Stack * stack )
{
	if ( stack -> 	head == NULL )
	{
		return 0;
	}
	int count = 1;
	StackNode * head = stack -> head;
	while ( head -> next != NULL )
	{
		count++;
		head = head -> next;
	}

	return count;
}

/**
 * Read a Huffman Coding Tree (in text format) from 'fp'.
 */
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	char input;
	int value;
	Stack * stack;
	stack = Stack_create();
	HuffNode * tree;
	StackNode * node;
	while ( !feof( fp ) )
	{
		input = fgetc( fp );
		if ( input == '1' )
		{
			//	PUSH
			value = (int) fgetc( fp );
			tree = HuffNode_create( value );
			Stack_pushFront( stack, tree );
		}
		else if ( input == '0' && numElementsInStack( stack ) > 1 )
		{
			//	POP POP COMBINE PUSH
			Stack_popPopCombinePush( stack );
		}
		else
		{
			//	DONE BUILDING TREE
			node = stack -> head;
			tree = node -> tree;
			Stack_destroy(stack);
			return tree;		//	RETURN HUFFTREE
		}
	}

	return NULL;
}

/**
 * Read a Huffman Coding Tree (in binary format) from 'fp'.
 * You will need to (conceptually) read a file a bit at a time. See the README
 * for hints on how to do this.
 */
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{

	return NULL;
}
