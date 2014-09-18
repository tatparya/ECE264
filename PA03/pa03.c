#include <stdio.h>
#include "answer03.h"

int main(int argc, char * * argv)
{
	
	
	// Testing explode function	
	
	int len;
	int i = 0;

	char ** strArr = explode ( "The\nTurning test", " \t\v\n\r\f", &len ); 
	
	if ( strArr != NULL )
	{
			for ( i = 0; i < len ; i++ ) 
				printf( "strArr = %s\n", strArr[i] );
	}
	//	EXPLODE ends here

    return EXIT_SUCCESS;
}

