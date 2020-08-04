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

/* Function: readMaze
 * ------------------
 * Reads a maze from a file to the data structure
 *
 * fileLocation: location of the file with maze
 *
 * returns: Returns MazeData with loaded values or NULL if error occurred
 */
MazeData *readMaze(char* fileLocation);

/* Function: printMaze
 * -------------------
 * Prints maze to the console
 *
 * m_mazeData: data structure with maze
 */
void printMaze(MazeData *m_mazeData);

/* Function: destroyMazeData
 * -------------------------
 * Deallocate memory in the MazeData data structure
 *
 * m_mazeData: data structure with information
 */
void destroyMazeData(MazeData *m_mazeData);

/* Function: saveMaze
 * ------------------
 * Saves the solution to the file of the location m_fileLocation. In case the file is not possible
 * to be open or created, displays the error message (Not a critical)
 *
 * fileLocation: Location of the file where maze should be saved
 * m_mazeData: Maze to be saved
 */
void saveMaze(char* fileLocation, MazeData *m_mazeData);

// Function Testing all functions in storage
void storage_Test();