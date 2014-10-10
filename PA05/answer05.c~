#include <stdio.h>
#include <stdlib.h>

#include "answer05.h"

void printArray ( int * arr, int length )
{
	//	PRINT ARRAY
	int i = 0;				// To go through array
	printf ( "= %d ", arr[i] );
	for ( i = 1; i < length; i++ )
	{
		printf ( "+ %d ", arr[i] );
	} 
	printf ( "\n" );
}

//	1
void partitionAll_fn ( int * arr, int index, int value ) 
{
	//	Check value for base case
	if ( value > 0 )
	{
		//	RECURSIVE CASE
		int val;
		for ( val = 1; val <= value; val++ )
		{
			arr[index] = val;
			partitionAll_fn ( arr, index + 1, value - val );
		}
	}
	else if ( value == 0 )
	{
		//	BASE CASE
		printArray ( arr, index );
	}
}

void partitionAll ( int value )
{
	int * arr;				//	Array to store partition
	int index = 0;				//	To store index value
	
	//	Allocate array to value
	arr = malloc ( sizeof ( int ) * value );
	
	//	Partition function call
	partitionAll_fn ( arr, index, value );
	
	//	Free array to avoid memory leak
	free ( arr );
}

//	2
void partitionIncreasing_fn ( int * arr, int index, int value, int lastVal ) 
{
	//	Check value for base case
	if ( value > 0 )
	{
		//	RECURSIVE CASE
		int val;
		for ( val = 1; val <= value; val++ )
		{
			if ( lastVal < val )
			{
				arr[index] = val;
				partitionIncreasing_fn ( arr, index + 1, value - val, val );
			}
		}
	}
	else if ( value == 0 )
	{
		//	BASE CASE
		printArray ( arr, index );
	}
}

void partitionIncreasing ( int value )
{
	int * arr;				//	Array to store partition
	int index = 0;				//	To store index value
	
	//	Allocate array to value
	arr = malloc ( sizeof ( int ) * value );
	
	//	Partition function call
	partitionIncreasing_fn ( arr, index, value, 0 );
	
	//	Free array to avoid memory leak
	free ( arr );	
}

//	3
void partitionDecreasing_fn ( int * arr, int index, int value, int lastVal ) 
{
	//	Check value for base case
	if ( value > 0 )
	{
		//	RECURSIVE CASE
		int val;
		for ( val = 1; val <= value; val++ )
		{
			if ( lastVal == 0 || lastVal > val )
			{
				arr[index] = val;
				partitionDecreasing_fn ( arr, index + 1, value - val, val );
			}
		}
	}
	else if ( value == 0 )
	{
		//	BASE CASE
		printArray ( arr, index );
	}
}

void partitionDecreasing ( int value )
{
	int * arr;				//	Array to store partition
	int index = 0;				//	To store index value
	
	//	Allocate array to value
	arr = malloc ( sizeof ( int ) * value );
	
	//	Partition function call
	partitionDecreasing_fn ( arr, index, value, 0 );
	
	//	Free array to avoid memory leak
	free ( arr );	
}

//	4
void partitionOdd_fn ( int * arr, int index, int value ) 
{
	//	Check value for base case
	if ( value > 0 )
	{
		//	RECURSIVE CASE
		int val;
		for ( val = 1; val <= value; val++ )
		{
			if ( val % 2 != 0 )
			{
				arr[index] = val;
				partitionOdd_fn ( arr, index + 1, value - val );
			}
		}
	}
	else if ( value == 0 )
	{
		//	BASE CASE
		printArray ( arr, index );
	}
}

void partitionOdd ( int value )
{
	int * arr;				//	Array to store partition
	int index = 0;				//	To store index value
	
	//	Allocate array to value
	arr = malloc ( sizeof ( int ) * value );
	
	//	Partition function call
	partitionOdd_fn ( arr, index, value );
	
	//	Free array to avoid memory leak
	free ( arr );	
}

//	5
void partitionEven_fn ( int * arr, int index, int value ) 
{
	//	Check value for base case
	if ( value > 0 )
	{
		//	RECURSIVE CASE
		int val;
		for ( val = 1; val <= value; val++ )
		{
			if ( val % 2 == 0 )
			{
				arr[index] = val;
				partitionEven_fn ( arr, index + 1, value - val );
			}
		}
	}
	else if ( value == 0 )
	{
		//	BASE CASE
		printArray ( arr, index );
	}
}

void partitionEven ( int value )
{
	int * arr;				//	Array to store partition
	int index = 0;				//	To store index value
	
	//	Allocate array to value
	arr = malloc ( sizeof ( int ) * value );
	
	//	Partition function call
	partitionEven_fn ( arr, index, value );
	
	//	Free array to avoid memory leak
	free ( arr );
}

//	6
void partitionOddAndEven_fn ( int * arr, int index, int value, int lastVal ) 
{
	//	Check value for base case
	if ( value > 0 )
	{
		//	RECURSIVE CASE
		int val;
		for ( val = 1; val <= value; val++ )
		{
			if ( lastVal == 0 || ( ( lastVal % 2 != 0 ) && ( val % 2 == 0 ) ) || ( ( lastVal % 2 == 0 ) && ( val % 2 != 0 ) ) )
			{
				arr[index] = val;
				partitionOddAndEven_fn ( arr, index + 1, value - val, val );
			}
		}
	}
	else if ( value == 0 )
	{
		//	BASE CASE
		printArray ( arr, index );
	}
}

void partitionOddAndEven ( int value )
{
	int * arr;				//	Array to store partition
	int index = 0;				//	To store index value
	
	//	Allocate array to value
	arr = malloc ( sizeof ( int ) * value );
	
	//	Partition function call
	partitionOddAndEven_fn ( arr, index, value, 0 );
	
	//	Free array to avoid memory leak
	free ( arr );
}

//	7
int isPrime ( int num )
{
	//	CHECK IF NUMBER IS PRIME
	int i;
	int notPrime = 0;
	for ( i = 2; i < num; i++ )
	{
		if ( num % i == 0 )
		{
			notPrime++;
		}
	} 
	
	if ( notPrime )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void partitionPrime_fn ( int * arr, int index, int value ) 
{
	//	Check value for base case
	if ( value > 0 )
	{
		//	RECURSIVE CASE
		int val;
		for ( val = 1; val <= value; val++ )
		{
			if ( isPrime ( val ) && val != 1 )
			{
				arr[index] = val;
				partitionPrime_fn ( arr, index + 1, value - val );
			}
		}
	}
	else if ( value == 0 )
	{
		//	BASE CASE
		printArray ( arr, index );
	}
}

void partitionPrime ( int value )
{
	int * arr;				//	Array to store partition
	int index = 0;				//	To store index value
	
	//	Allocate array to value
	arr = malloc ( sizeof ( int ) * value );
	
	//	Partition function call
	partitionPrime_fn ( arr, index, value );
	
	//	Free array to avoid memory leak
	free ( arr );
}


