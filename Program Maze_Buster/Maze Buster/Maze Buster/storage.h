#pragma once
// Structures

/*
* struct _Node: structure responsible for storing information of each cell in the maze
*     Stores the information about the walls, current step, heuristics, path taken to get to the node,
*     And the parent (previous node of the solution path)
*/
typedef struct _Node Node;
struct _Node {
	int walls, step, g, x, y;
	char path;
	Node * parent;
};


/*
* struct _MazeData: Main structure required for solving the maze.
*     Stores the size, start and finish position in the table info[6]
*     Stores the array of Nodes in the maze
*     Stores the solution length and the solution char table
*/
typedef struct _MazeData MazeData;
struct _MazeData {
	int info[6];
	Node **maze;
	char *solution;
	int solutionL;
};

// Functions Declaration
MazeData *readMaze(char* fileLocation);
void printMaze(MazeData *m_mazeData);
void destroyMazeData(MazeData *m_mazeData);
void saveMaze(char* fileLocation, MazeData *m_mazeData);

// Function Testing all functions in storage
void storage_Test();