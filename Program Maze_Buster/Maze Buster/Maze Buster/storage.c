#include "storage.h"

#include <stdio.h>
#include <stdlib.h>

// Functions Initialization

/*
* *readMaze(char* m_fileLocation): returns a pointer to the structure, which holds
*     the maze read from the file passed in m_fileLocation
*/
MazeData *readMaze(char* m_fileLocation)
{
	// Opening file and ensuring it is open properly.
	FILE *m_inputMaze = NULL;
	if (fopen_s(&m_inputMaze, m_fileLocation, "rt") != 0)
	{
		printf("Error. Failed to open the file with the maze.\n");
		return NULL;
	}

	// Reading first 6 values, gaining information about: 
	// Size of the maze, starting and ending positions
	int m_info[6];
	for (int i = 0; i < 6; i++)
	{
		if( fscanf_s(m_inputMaze, "%d", &m_info[i]) != 1 )
		{
			// Failure in reading the file (File is corrupted)
			printf("Error. File is corrupted or incomplete.\n");
			return NULL;
		}
		if (m_info[i] > 100000 || m_info[i] < 0)
		{
			printf("Error. Size of the maze exceeds maximum of 100,000. Try smaller maze.\n Max Ram usage is 2GB.\n");
			return NULL;
		}
	}

	// Allocating memory for the maze
	Node **m_maze = NULL;
	m_maze = (Node **)calloc(m_info[0], sizeof(Node *));
	for (int i = 0; i < m_info[0]; i++)
	{
		m_maze[i] = (Node *)calloc(m_info[1], sizeof(Node));
	}

	// Checking if allocation was successful
	if (!m_maze)
	{
		printf("Error. Could not allocate the memory.\n");
		return NULL;
	}

	// Reading maze from the file
	for (int i = 0; i < m_info[0]; i++)
	{
		for (int j = 0; j < m_info[1]; j++)
		{
			if(fscanf_s(m_inputMaze, "%d", &m_maze[i][j].walls) != 1)
			{
				// Failure in reading the file (File is corrupted)
				printf("Error. File is corrupted or incomplete.\n");
				return NULL;
			}
			if (m_maze[i][j].walls > 15 || m_maze[i][j].walls < 0)
			{
				printf("Error. File has read a value above permitted one.\n");
				return NULL;
			}
			m_maze[i][j].x = j;
			m_maze[i][j].y = i;
		}
	}

	// Checking if START & FINISH in the maze
	for (int i=0; i < 2; i++)
	{
		if (m_info[0 + i] <= m_info[2 + i] || m_info[0 + i] <= m_info[4 + i])
		{
			printf("Error. Start or Finish out of the maze's scope.\n");
			return NULL;
		}
	}

	// Closing the files as no more reading requited
	if (fclose(m_inputMaze) != 0)
	{
		printf("It is very bad, file was not closed.\n");
	}

	// Checking the borders are correct in the maze
	// The incorrect values would cause error in memory reading
	// Checking First and Last vertical border
	int up = 8, down = 2, left = 4, right = 1;
	for (int i = 0; i < m_info[0]; i++)
	{
		if ((m_maze[i][0].walls & left) == 0 )
		{
			printf("Cell [%d][0] corrected.", i);
			m_maze[i][0].walls = m_maze[i][0].walls + left;
		}
		if ((m_maze[i][m_info[1] - 1].walls & right) == 0)
		{
			printf("Cell [%d][%d] corrected.", i, (m_info[1]-1));
			m_maze[i][m_info[1] - 1].walls = m_maze[i][m_info[1] - 1].walls + right;
		}
	}
	// Checking First and Last horizontal border
	for (int i = 0; i < m_info[1]; i++)
	{
		if ((m_maze[0][i].walls & up) == 0)
		{
			printf("Cell [0][%d] corrected.", i);
			m_maze[0][i].walls = m_maze[0][i].walls + up;
		}
		if ((m_maze[ m_info[0]-1 ][i].walls & down) == 0)
		{
			printf("Cell [%d][%d] corrected.", (m_info[0] - 1), i);
			m_maze[m_info[0] - 1][i].walls = m_maze[m_info[0] - 1][i].walls + down;
		}
	}

	// Creating MazeData structure and allocating obtained data
	MazeData *md = (MazeData*)malloc(sizeof(MazeData));
	for (int i = 0; i < 6; i++)
	{
		md->info[i] = m_info[i];
	}
	md->maze = m_maze;
	md->solution = NULL;
	md->solutionL = 0;
	return md;
}


/*
* void printMaze(MazeData *md): prints the maze on the screen in the console 
*/
void printMaze(MazeData *md)
{
	if (md == NULL)
	{
		printf("Error. Not possible to display maze as the structure MazeData is corrupted.\n");
		return;
	}
	// Creating constants that allow to check the walls
	int m_right = 1, m_down = 2, path = 32;
	// Variables to store objects to display
	int next = 0, cur = 0;
	
	// Displaying signs:
	// 32 - ' ' - a empty sign
	// 70 - 'F' - Big letter F to mark the Finish
	// 83 - 'S' - Big letter S to mark the Start
	// 158 - 'x' - Centered x to mark the solution path
	// 219 - A solid block to mark the body of the maze (walls)
	int m_block = 219, m_empty = 32, m_mark = 158, m_F = 70, m_S = 83;

	// Drawing the top border
	for (int j = 0; j < (md->info[1] * 2) + 1; j++)
	{
		printf("%c", m_block);
	}
	printf("\n");

	// Each row gives information to print two lines
	for (int i = 0; i < md->info[0]; i++)
	{
		// Prints the first line
		printf("%c", m_block);
		for (int j = 0; j < md->info[1]; j++)
		{
			// Decision about the current node
			cur = m_empty;
			if (md->info[2] == i &&  md->info[3] == j)
			{
				cur = m_S;
			}
			else if (md->info[4] == i &&  md->info[5] == j)
			{
				cur = m_F;
			}
			else if ((md->maze[i][j].walls & path) != 0)
			{
				cur = m_mark;
			}
			// Node adjacent to the current
			if ((md->maze[i][j].walls & m_right) == 0)
			{
				next = m_empty;
			}
			else
			{
				next = m_block;
			}
			printf("%c%c", cur, next);
		}

		// Prints the second line
		printf("\n%c", m_block);
		for (int j = 0; j < md->info[1]; j++)
		{
			if ((md->maze[i][j].walls & m_down) == 0)
			{
				next = m_empty;
				if ((md->maze[i][j].walls & path) != 0)
				{
					cur = m_mark;
				}
			}
			else
			{
				next = m_block;
			}
			printf("%c%c", next, m_block);
		}
		printf("\n");
	}
	return;
}


/*
* void destroyMazeData(MazeData *md):The functions free the memory allocated in the MazeData 
*     structure to prevent any memory leakage.
*/
void destroyMazeData(MazeData *md)
{
	// Free the nodes of the maze
	for (int i = 0; i < md->info[0]; i++)
	{
		free(md->maze[i]);
	}
	free(md->maze);

	// Free the solution (String)
	free(md->solution);

	// Free the MazeData structure
	free(md);
	md = NULL;	
	return;
}


/*
* saveMaze(char* m_fileLocation, MazeData *md): Saves the solution to the file of the
*     location m_fileLocation. In case the file is not possible to be open or created, displays
*     the error message (Not a critical)
*/
void saveMaze(char* m_fileLocation, MazeData *md)
{
	// Opening file to save the solution
	FILE *m_file;
	if (fopen_s(&m_file, m_fileLocation, "w") != 0)
	{
		printf("Unsuccessful Save\n");
		return;
	}
	else
	{
		fprintf_s(m_file, "%d\n", md->solutionL);
		// Writing to the file
		for (int i = 1; i < md->solutionL+1; i++)
		{
			fprintf_s(m_file, "%c", md->solution[i]);
		}
	
		// Closing the file
		if (fclose(m_file) != 0)
		{
			printf("It is very bad, file was not closed.\n");
		}
	}
	return;
}


/*
* void storage_Test(): Make automated tests to the most of the functions in the storage.h.
*     In case a test is failed displays the error message
*/
void storage_Test(){

	// Testing the read function on a small pre-made file m1Test
	// Test 1 - No file name given
	MazeData *d_test = readMaze("dddd.txt");
	if (d_test == NULL)
	{
		printf("Storage Test 1 Passed: No name resilient.\n");
	}

	// Test 2 - Empty File
	d_test = readMaze("Testing/mTest2.txt");
	if (d_test == NULL)
	{
		printf("Storage Test 2 Passed: Empty file resilient.\n");
	}

	// Test 3 - Start is outside the maze
	d_test = readMaze("Testing/mTest3.txt");
	if (d_test == NULL)
	{
		printf("Storage Test 3 Passed: Start outside boundaries resilient.\n");
	}

	// Test 4 - Finish is outside the maze
	d_test = readMaze("Testing/mTest4.txt");
	if (d_test == NULL)
	{
		printf("Storage Test 4 Passed: Finish outside boundaries resilient.\n");
	}

	// Test 5 - Letter rather than a number
	d_test = readMaze("Testing/mTest5.txt");
	if (d_test == NULL)
	{
		printf("Storage Test 5 Passed: Letter resilient.\n");
	}

	// Test 6 - Number bigger than 15
	d_test = readMaze("Testing/mTest6.txt");
	if (d_test == NULL)
	{
		printf("Storage Test 6 Passed: Incorrect number resilient.\n");
	}

	// Test 7 - Size of the maze bigger than 100,000 in any direction
	d_test = readMaze("Testing/mTest7.txt");
	if (d_test == NULL)
	{
		printf("Storage Test 7 Passed: Bigger than max size resilient.\n\n");
	}
}