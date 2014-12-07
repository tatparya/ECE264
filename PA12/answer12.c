#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "answer12.h"

typedef struct ThreadData
{
	uint128 threadRange;	//	Thread range 	eg. 5, 6, 7 = 3
	uint128 startValue;		//	Start of range 	eg. 5
	uint128 endValue;		//	End of Range 	eg. 7
	int numDivisors;	//	Result
	uint128 value;		//	Input

} data;

//	To check if a charecter is a space
int my_isspace(int ch)
{
	int res;

	if ( ch == ' ' || ch == '\f' || ch == '\n' || ch == '\t' || ch == '\v' || ch == '\r' )
	{	
		res = 1;
	}
	else 
	{
		res = 0;
	}
	return res;
}

/**
 * Convert the initial portion of C-string 'str' to an unsigned 128-bit integer
 *
 * This function should be just like atoi(...), except that it returns an 128
 * bit unsigned integer. Return 0 on any error. Don't forget you must skip 
 * white-space.
 *
 * See PA02 for hints on implementing this function.
 */
uint128 alphaTou128(const char * str)
{
	uint128 result = 0;
	int i = 0;
	int minus = 1;
	int isChar = 0;

	while ( my_isspace ( str[i] ) )	//	TODO is space
	{
		i++;
	}

	if ( str[i] == '-' )
	{
		minus = -1;
		i++;
		//	ERROR
		return 0;
	}
	else if ( str[i] == '+' )
	{
		minus = 1;
		i++;
	}

	while ( str[i] != '\0' && !isChar )
	{
		if ( (int) str[i] >= 48 && (int) str[i] <= 57 )
		{
			result = result * 10 + (int) str[i] - 48;
			i++;		
		}
		else
		{
			isChar++;
		}
	}

	return result * minus;
}

/**
 * Return a newly allocated C-string which represents the passed value.
 * The caller is responsible for freeing the allocated string.
 *
 * If you have already implemented alphaTou128(...) (see hint), then you should
 * be able to figure out how to implement u128ToString(...).
 */
char * u128ToString(uint128 value)
{
	char * result;
	uint128 copy = value;
	int count = 0;

	if ( value == 0 )
	{
		result = malloc ( sizeof ( char ) + 1 );
		result[0] = (char)48;
		result[1] = '\0';

		return result;
	}

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
		result[count] = (char) ( value % 10 + 48 );
		value = value / 10; 
		count--;
	}

	return result;
}

void createThreadDataStruct( struct ThreadData * threadStructPtr, uint128 threadRange, uint128 value, uint128 sqroot, int i )
{
	threadStructPtr -> threadRange = threadRange;
	threadStructPtr -> startValue = ( threadRange * i ) + 1;
	if ( threadStructPtr -> startValue + threadRange - 1 <= sqroot )
	{
		threadStructPtr -> endValue = ( threadStructPtr -> startValue + threadRange ) - 1;
	}
	else
	{
		//	Handling last thread case
		threadStructPtr -> endValue = sqroot;
	}
	
	threadStructPtr -> value = value;
	threadStructPtr -> numDivisors = 0;
}

void * primeTest( void * pointer )
{
	//	Typecast incoming arg
	struct ThreadData * dataStruct = ( struct ThreadData * ) pointer;
	uint128 ind;

	for ( ind = dataStruct -> startValue; ind <= dataStruct -> endValue; ind++ )
	{
		if ( dataStruct -> value != 2 * ind + 1 )
		{
			if ( dataStruct -> value % ( ( 2 * ind ) + 1 ) ==  0 )
			{
				dataStruct -> numDivisors++;
			}
		}
	
	}
	return NULL;
}

/**
 * Test is 'value' is prime.
 * 'n_threads' is the number of threads to create to complete this computation.
 * Return TRUE of FALSE.
 * 
 * LEAK NO MEMORY.
 *
 * Good luck!
 */
int primalityTestParallel(uint128 value, int n_threads)
{
	pthread_t trd[ n_threads ];
	struct ThreadData threadDataStruct[ n_threads ];
	int total = 0;

	//	Check for 2 and 3
	if ( value == 2 )
	{
		return 1;
	}

	//	Check if even
	if ( value % 2 == 0 )
	{
		return 0;
	}

	//	CALCULATE RANGE
	uint128 sqroot = sqrt( value );
	//	Total numbers to test = 2 .. sqroot

	//	Range for each thread but the last = sqroot - 2 / ( nthreads - 1 )
	uint128 threadRange;
	if ( n_threads > 1 )
	{
		threadRange = sqroot / n_threads;	
	}
	//	If the range is less than the number of threads
	if ( threadRange == 0 )
	{
		threadRange = 1;
	}

	//	CREATE THREADS
	int i;
	for ( i = 0; i < n_threads; i++ )
	{
		//	Populate thread data structure
		createThreadDataStruct( & threadDataStruct[i], threadRange, value, sqroot, i );
		int rtv;
		//	Creating the threads
		rtv = pthread_create( & trd[i], NULL, primeTest, (void *) & threadDataStruct[i] );
		if ( rtv != 0 )
		{
			fprintf( stderr, "The String could not be created\n" );
		}
	}

	//	Wait for threads to be created and executed

	for ( i = 0; i < n_threads; i++ )
	{
		int rtv;
		rtv = pthread_join( trd[i], NULL );
		if ( rtv != 0 )
		{
			fprintf( stderr, "Error joining the thread\n" );
		}
		total += threadDataStruct[i].numDivisors;
	}

	if ( total == 0 )
	{
		return 1;
	}
	
	return 0;
}