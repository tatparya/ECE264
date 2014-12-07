#include <stdlib.h>
#include <stdio.h>
#include "answer12.h"

int main(int argc, char const *argv[])
{
	char input[] = "3";
	uint128 value = alphaTou128( input );

	int result = primalityTestParallel( value, 4 );

	printf( "Result = %d\n", result );

	return 0;
}