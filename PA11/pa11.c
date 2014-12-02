#include <stdlib.h>
#include <stdio.h>
#include "answer11.h"
#include "treefun.h"

int main(int argc, char const *argv[])
{
	char filename[] = "inputs/07-description.bit-huff";
	char outfile[] = "output.txt";

	FILE * fp1, * fp2;
	fp1 = fopen ( filename, "r" );
	fp2 = fopen ( outfile, "wb" );
	HuffNode * tree = HuffTree_readTextHeader( fp1 );

	HuffNode_print( fp2, tree );
	fclose(fp1);
	fp1 = fopen(filename, "r");
	size_t len_ptr;
	unsigned char * str = Huffman_applyTree(fp1, tree, &len_ptr);

	printf("%s\n", str);

	return 0;
}