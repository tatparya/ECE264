#include <stdlib.h>
#include <stdio.h>

char * u128ToString( int input )
{
	char * result;
	int copy = input;
	int count = 0;

	while ( copy!= 0 )
	{
		copy /= 10;
		count++;
	}

	result = malloc ( sizeof( char ) * count + 1 );

	result[count] = '\0';
	count--;
	while ( !(count < 0 ) )
	{
		result[count] = (char) ( input % 10 + 48 );
		input = input / 10; 
		count--;
	}

	return result;
}

int main ()
{
	int input = 123456;
	char * result;
	result = u128ToString ( input );

	printf ( "%s\n", result );
	printf("HERE!!\n");
	return 0;
}