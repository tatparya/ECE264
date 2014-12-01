#include <stdlib.h>
#include <stdio.h>
#include "answer10.h"

int main(int argc, char const *argv[])
{
	
	const char businesses_path[] = "dataset/businesses.short.tsv";
	const char reviews_path[] = "dataset/reviews.short.tsv";

	struct YelpDataBST * data = create_business_bst( businesses_path, reviews_path);

	destroy_business_bst ( data );
	return 0;
}