#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE * fptr = NULL;	//	to hold the file ptr
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
		fgets ( str, 100, fptr );
		printf("%s\n", str);
		i++;
	}
	return 0;
}
