#include "answer06.h"
#include <stdio.h>

void print_loc(char** maze, int w, int h, int * loc) {
	// Print the maze to stdout.
	int x=0;
	int y=0;
	for(y=0; y < h; y++) {
		for ( x = 0; x < w; x++ ) {
			if ( loc [0] == y && loc [1] == x )
				printf("O");
			else
				printf("%c", maze[y][x]);
		}
		printf("\n");
	}
}

int find_entrance( char * * maze, int w );
int find_exit( char * * maze, int w, int h );
void setLocation ( int * location, int x, int y );
int numWaysToGo ( char * * maze, int w, int h, int * location, char facing );
void traverse ( char * * maze, int * currentLocation, char facing, int w, int h, char move);
int moveStep ( char * * maze, int * currentLocation, char movem, int w, int h );
char oppositeDir ( char dir );

void print_directions( char * * maze , int w, int h )
{
	int entrance;
	int currentLocation[2];
			
	//		FIND ENTRANCE AND EXIT POSITION
	entrance = find_entrance ( maze, w );
	setLocation ( currentLocation, 0, entrance );
	traverse( maze, currentLocation, 'S', w, h, 'S' );						// TRAVERSE!!
	//		PRINT DIRECTIONS
	
}

/*
	DIRECTION REFERENCE
	1 = EAST
	2 = WEST
	3 = SOUTH
	4 = NORTH
*/

//		MAIN FUNCTION TO TRAVERSE *****************************
void traverse ( char * * maze, int * currentLocation, char facing, int w, int h, char move )
{	
	//	MOVE TO NEW LOCATION
	if ( !moveStep( maze, currentLocation, move, w, h ) )
	{
		//	Can't Move further in the direction
		
		return;
	}
	else
	{
		printf( "%c 1\n", facing );
		maze[ currentLocation[0] ][ currentLocation[1] ] = '*';
	}
	//print_loc ( maze, w, h, currentLocation );
	//printf("\n");
	
	//-------------------------
	int numWays = 0;
	int LastRecursiveLocation [2];
	int i = 0;
	char * dir = { "WESN" };
	int j = 0;
	int tempLocation [2];
	int x,y;
	
	numWays = numWaysToGo ( maze, w, h, currentLocation, facing );
	
	//	p 	RECURSIVE CASE
	if ( numWays > 1 )
	{
		x = currentLocation[0];
		y = currentLocation[1];
		//printf ( "RECURSIVE CASE!!\n\n");
		setLocation ( LastRecursiveLocation, currentLocation[0], currentLocation[1] );
		setLocation ( tempLocation, currentLocation[0], currentLocation[1] );
		while ( i < numWays && j < 4 )
		{
			//	Go in all possible directions and come back!!
			if ( dir[j] != oppositeDir( facing ) && moveStep( maze, tempLocation, dir[j], w, h ) )
			{
				traverse( maze, currentLocation, dir[j], w, h, dir[j] );	// 		TRAVERSE!!
				setLocation( currentLocation, x, y );
				setLocation ( tempLocation, currentLocation[0], currentLocation[1] );
				i++;
			}
			j++;
		}
		
	}
	//	************************************************************
	
	//		NORMAL CASE 
	else if ( numWays == 1 )
	{
		//		Keep Going
		setLocation ( tempLocation, currentLocation[0], currentLocation[1] );
		if ( moveStep ( maze, tempLocation, facing , w, h ) )
		{
			traverse( maze, currentLocation, facing, w, h, facing );		// TRAVERSE!!
		}
		else if ( !moveStep ( maze, tempLocation, facing , w, h ) )
		{
			while ( j < 4 )
			{
				if (dir[j] != oppositeDir( facing ) && moveStep ( maze, tempLocation, dir[j], w, h ) )
				{
					traverse( maze, currentLocation, dir[j], w, h, dir[j] );		// TRAVERSE!!
					j = 4;
				}
				j++;
			}
		}
	}
	//	***************************************************************
	
	//		BASE CASE
	else if ( numWays == 0 )
	{
		//printf ( "BASE CASE!!\n\n" );
		//	GO BACK!!
	}
	
	printf("%c 1\n", oppositeDir(facing));
}

//		TO MOVE TO NEW LOCATION
int moveStep ( char * * maze, int * currentLocation, char move, int w, int h )
{
	int tempLocation [2];
	tempLocation[0] = currentLocation[0];
	tempLocation[1] = currentLocation[1];
	//		Move West
	if ( tempLocation[0] < h-1 )
	{
		if ( move == 'W' || move == 1 )
		{
			tempLocation[1]--;
			if ( maze[ tempLocation[0] ][ tempLocation[1] ] != 'X' )
				{
					currentLocation[1] = tempLocation[1];
						
					return 1;
				}
			else
				return 0;
		}
		//		Move East
		else if ( move == 'E' ||  move == 2 )
		{
			tempLocation[1]++;
			if ( maze[ tempLocation[0] ][ tempLocation[1] ] != 'X' )
				{
					currentLocation[1] = tempLocation[1];
					
					return 1;
				}
			else
				return 0;
		}
		//		Move South
		else if ( move == 'S' || move == 3 )
		{
			tempLocation[0]++;
			if ( maze[ tempLocation[0] ][ tempLocation[1] ] != 'X' )
				{
					currentLocation[0] = tempLocation[0];
					
					return 1;
				}
			else
				return 0;
		}	
		//		Move North
		else if ( move == 'N' || move == 4 )
		{
			tempLocation[0]--;
			if ( maze[ tempLocation[0] ][ tempLocation[1] ] != 'X' )
				{
					currentLocation[0] = tempLocation[0];
				
					return 1;
				}
			else
				return 0;
		}
	}	
	
	return 0;
}

//		TO FIND OPPOSITE DIRECTION
char oppositeDir ( char dir )
{
	if ( dir == 'E' )
		return 'W';
	else if ( dir == 'W' )
		return 'E';
	else if ( dir == 'N' )
		return 'S';
	else
		return 'N';
}
//		TO FIND NUMBER OF WAYS WE CAN GO	-------------------
int numWaysToGo ( char * * maze, int w, int h, int * location, char facing )
{
	int numWays = 0;
	
	if ( location[0] < h-1 )
	{
		//	West	
		if ( ( facing != 'E' ) && ( maze [ location[0] ][ location [1] - 1 ] == ' ' ) )
		{
			numWays++;		
		}	
		//	East
		if ( ( facing != 'W' ) && ( maze [ location[0] ][ location [1] + 1 ] == ' ' ) )
		{
			numWays++;		
		}	
		//	North
		if ( ( facing != 'S' ) && ( maze [ location[0] - 1 ][ location [1] ] == ' ' ) )
		{
			numWays++;		
		}	
		//	South
		if ( ( facing != 'N' ) && ( maze [ location[0] + 1 ][ location [1] ] == ' ' ) )
		{
			numWays++;		
		}	
	}
	return numWays;
}

//		TO SET CURRENT LOCATION		-----------------
void setLocation ( int * location, int x, int y )
{
	location [0] = x;
	location [1] = y;
}

//		TO FIND ENTRANCE LOCATION	-----------------
int find_entrance( char * * maze, int w )
{
	int entrance;
	int i;		
	for ( i = 0; i < w; i++ )
	{
		if ( maze[0][i] == ' ' )
		{
			entrance = i;
		}
	}
	
	return entrance;
}

//		TO FIND EXIT LOCATION	--------------------
int find_exit( char * * maze, int w, int h)
{
	int exit;
	int i;		
	for ( i = 0; i < w; i++ )
	{
		if ( maze[h-1][i] == ' ' )
		{
			exit = i;
		}
	}
	
	return exit;
}


