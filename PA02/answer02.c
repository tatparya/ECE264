#include "answer02.h"

// Function to print the length of the str that is passed into it
size_t my_strlen ( const char * str )
{
	int ct=0;
	int i=0;

	while ( str[i] != '\0' )
	{
		ct++;
		i++;
	}

	return ct;
}

// To count the number of occurences of charecter 'ch' in str
int my_countchar (const char * str, char ch)
{
	int ct=0;
	int i=0;

	while ( str[i] != '\0' )
	{
		if ( str[i] == ch )
		{
			ct++;
		}
		i++;
	}
	
	return ct;
}

char * my_strchr(const char * str, int ch)
{
	int i=0;
	int found = 0;

	do
	{
		if ( str[i] == ch )
		{
			found++;
		}
		else
		{
			i++;
		}
	}
	while ( str[i] != '\0' && !found );

	if ( found )
	{
		return str[i-1];
	}
	else
	{
		return NULL;
	}
}

char * my_strrchr(const char * str, int ch)
{
	int i=0;
	int found=0;

	do
	{
		i++;
	}
	while ( str[i] != '\0' );

	while ( i > 0 && !found )
	{
		if ( str[i] == ch )
		{
			found++;
		}
		else
		{
			i--;
		}
	}
	
	if ( found )
	{
		return str[i];
	}
	else
	{
		return NULL;
	}
}

char * my_strstr(const char * haystack, const char * needle)
{
	int i=0;
	int empty=0;	// To check the number of elements in the string
	int k;
	int l;
	int found=0;
	int same;

	while ( haystack[i] != '\0' && !found )
	{
		k = 0;
		same=1;
		l=i;
		while ( needle[k] != '\0' && same )
		{		
			if (  needle[k] != haystack[l] )
			{
				same--;
			}
			k++;
		}
		if ( same )
		{
			found++;
		}
		i++;
		num++;
	}

	if ( empty )
	{
		return haystack;
	}
	else if ( found )
	{
		return haystack[i];
	}
	else 
	{
		return NULL;
	}
}

char * my_strcpy(char * dest, const char * src)
{
	int i=0;

	do
	{
		dest[i] = src[i];
	}
	while ( src[i] != '\0' );

	return dest;
}

char * my_strcat(char * dest, const char * src)
{

	int i=0;
	int j=0;

	while ( dest[i] != '\0' )
	{
		i++;
	}
	do
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	while ( src[j] != '\0' );
	
	return dest;
}

int my_isspace(int ch)
{
	res;

	if ( ch == ' ' || ch == '\f' || ch == '\n' || ch == '\t' || ch == '\v' )
	{
		res = 1;
	}
	else 
	{
		res = 0;
	}
	return res;
}

int my_atoi(const char * str)
{
	int ret=0;
	int i=0;
	int minus=1;
	int ischar = 0;

	{
		i++;
	}
	while ( my_isspace ( str[i] );
	
	if ( str[i] == '-' )
	{
		minus = -1;
		i++;
	}

	else if ( str[i] == '+' )
	{
		minus = 1;
		i++;
	}

	while ( str[i] != '\0' || !ischar )
	{
		if ( str[i] >= 0 || str[i] <= 9 )
		{
			i++;
			ret = ret * 10 + str[i]; 
		}
		else
		{
			ischar++;
		}
	}

	return ret;
}
