#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	char filename[] = "inputs/07-description.bit-huff";

	FILE * fp;
	fp = fopen ( filename, "r" );
	int count = 0;
	int val;
	while ( !feof( fp ) )
	{
		val = fgetc(fp);
		printf ( "%d  |", val );
		printf ( "  %c\n", (char)val );
		count++;
	}
	printf ( "COunt = %d\n", count );
	return 0;
}