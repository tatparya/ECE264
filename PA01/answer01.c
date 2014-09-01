#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
	int i;
	int sum = 0;
	for ( i = 0; i < len; i++ )
	{
		sum += array[i];
	} 
	return sum;
}

int arrayCountNegative(int * array, int len)
{
	int i;
	int ct = 0;
	for ( i = 0; i < len; i++ )
	{
		if ( array[i] < 0 )
		{
			ct++;
		}
	}
	return ct;
}

int arrayIsIncreasing(int * array, int len)
{    
    
	int i;
	int result;
	int flag = 0;
	for ( i = 0; i < len - 1; i++ )
	{
		if ( array[i] > array[i + 1] )
		{
			flag++;
		}
	}
	
	if ( !flag )
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
    int i = len - 1;
	int index;
	int found = 0;
	while ( ( i >= 0 ) && ( !found ) )
	{
		if ( haystack[i] == needle )
		{
			index = i;
			found++;
		}
		i--;
	}

	if ( !found )
	{
		index = -1;
	}

	return index;
}

int arrayFindSmallest(int * array, int len)
{
    int smallest = len - 1;
	int i;
	
	for ( i = len - 2; i >= 0; i-- )
	{
		if ( array[i] <= array[smallest] )
		{
			smallest = i;
		}
	}
	if ( len == 0 )
	{
		smallest = 0;
	}
	return smallest;
}
