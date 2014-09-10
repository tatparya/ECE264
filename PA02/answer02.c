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
	int k=0;
	int l=0;
	int found=0;

	while ( haystack[i] != '\0' )
	{
		while ( needle[i] != '\0' )
		{
			if
}
char * my_strcpy(char * dest, const char * src)
{

}

char * my_strcat(char * dest, const char * src)
{

}

int my_isspace(int ch)
{

}

int my_atoi(const char * str)
{

}
