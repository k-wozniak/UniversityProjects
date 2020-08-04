#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithm.h"
#include "storage.h"
#include "linkList.h"

// Main
int main(int argc, char** argv)
{
	// Variable used to decide either test should or should not be performed
	int test = 0;

	// Variable implementation
	char *fLocation = NULL, *fDestination = NULL;
	short int cla_d = 0;
	MazeData *mazeData = NULL;

	// Checking & saving the input parameters and deciding
	// -d if to draw a maze
	// Checks for validity of the number of arguments supplied against expected one
	if (2 < argc < 5)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-d") == 0)
			{
				cla_d = 1;
			}
			else
			{
				if (fLocation == NULL)
				{
					fLocation = argv[i];
				}
				else
				{
					fDestination = argv[i];
				}
			}
		}
	}
	else
	{
		printf("Incorrect number of arguments supplied.\n");
		return -1;
	}

	// Tests
	if (test == 1)
	{
		printf("Extreme Case Tests:\n");
		storage_Test();
		printf("Functionality Tests:\n");
		algorithm_Test();
		linkList_Test();
		printf("Tests complete.\n\n");
		printf("\nPress Enter to Continue");
		while (getchar() != '\n');
	}

	// Loading the maze from the .txt file, if fail return a failure
	// message & close the program, if not creates an object
	// to describe the maze in the memory
	mazeData = readMaze(fLocation);
	if (mazeData == NULL)
	{
		return -1;
	}

	// BreathSearch or deepSearchir something (maybe random one)
	// Execute algorithm
	MazeData *dae = findMazeSolution(mazeData);
	
	// If solution was not found the save function and print is not called 
	if (dae != NULL)
	{
		// Save algorithm to the file
		saveMaze(fDestination, mazeData);

		// Depending on input print or not the solution
		if (cla_d == 1)
		{
			printMaze(mazeData);
		}
	}
	else
	{
		printf("No solution found\n");
	}

	// Delete all the memory used/allocated
	destroyMazeData(mazeData);
	mazeData = NULL;
	
	// This stops our program from exiting when done, so we can
	//see the message that was displayed.	
	printf("\nPress Enter to Continue");
	while (getchar() != '\n');

	_CrtDumpMemoryLeaks();
	return 0;
}