#include "algorithm.h"

#include "linkList.h"
#include "storage.h"

#include <stdio.h>
#include <stdlib.h>

// Functions Initialization

/* 
* findMazeSolution(MazeData *md): returns a pointer to the structure if a solution 
*     to the maze (passed inside md) was found, otherwise, returns NULL
*/
MazeData *findMazeSolution(MazeData *md)
{
	// Simple error check
	if (md == NULL)
	{
		printf("Error. Not possible to display maze as the structure MazeData is corrupted.\n");
		return NULL;
	}

	// Creating lists, first stores unexplored nodes
	List *openList = (List*)malloc(sizeof(List));
	openList->count = 0;
	openList->head = NULL;
	
	// Finding and populating the first step
	Node *curNode = &md->maze[md->info[3]][md->info[2]];
	populateNode(curNode, NULL, 0, md->info[5], md->info[4], ' ');
	markAsVisited(curNode);
	addFirst(openList, curNode);
	
	// The algorithm (A*)
	Node *newNode = NULL;
	while (isEmpty(openList) == 0) // Maze had no solution if opneList is empty (all possible nodes visited)
	{
		curNode = removeFirst(openList);	// Takes the closest node to the finish
		for (int i = 1; i < 9; i=i*2)		// Checks all 4 neighbors of the given node
		{
			newNode = returnNeighbour(i, curNode, md);
			if (newNode != NULL)			// If returned node is NULL then not valid therefore, ignored
			{
				markAsVisited(newNode);
				if (isFinish(newNode, md) == 1)	// If finished algorithm backtrack the solution and leaves
				{
					backtrackSolution(newNode, md);
					destroyLinkList(openList);	// Before exiting all data are cleaned (allocated memory freed)
					return md;					
				}
				else
				{
					// If the node is valid but no solution, then is added to the open list for future expansion
					insertNodeSorted(openList, newNode);	
				}
			}
		}
	}

	// In case there is no solution:
	// Destroy all allocated memory
	destroyLinkList(openList);
	md->solution = NULL;
	md->solutionL = 0;
	// Return NULL as no solution has been found
	return NULL;
}


/*
* int heuristic(int c_x, int c_y, int f_x, int f_y, int step): return heuristics of a current position (c_x & c_y)
*     based on the Manhattan distance to the target and the current step
*/
int heuristic(int c_x, int c_y, int f_x, int f_y, int step)
{
	return (step + abs(f_x - c_x) + abs(f_y - c_y));
}


/*
* Node *returnNeighbour(int direction, Node *node, MazeData *md): return a pointer of the neighbor in the 
*     direction  given by the integer 'direction'(1 - right, 2 - down, 4 - left, 8 - up). If neighbor does not
*     exist returns NULL.
*/
Node *returnNeighbour(int direction, Node *node, MazeData *md)
{
	char path;
	// Checks if there is a wall in a given direction
	if ((node->walls & direction) == 0)
	{	
		// Given the direction returns coordinates of the new node
		int xDelta = node->x, yDelta = node->y;
		switch (direction)
		{
			case 1:
				xDelta = xDelta + 1;
				path = 'R';
				break;
			case 2:
				yDelta = yDelta + 1;
				path = 'D';
				break;
			case 4:
				xDelta = xDelta - 1;
				path = 'L';
				break;
			case 8:
				yDelta = yDelta - 1;
				path = 'U';
				break;
			default:
				return NULL;
		}
		// Checks if it is in the boundary of the maze
		if (xDelta >= 0 && yDelta >= 0 && xDelta < md->info[1] && yDelta < md->info[0])
		{
			Node *newNode = &md->maze[yDelta][xDelta];
			// Returns only unchecked nodes 
			if (isVisited(newNode) == 0)
			{
				populateNode(newNode, node, (node->step + 1), md->info[5], md->info[4], path);
				return newNode;
			}
		}
	}
	// If in the given direction there is no node returns NULL
	return NULL;
}


/*
* void populateNode(Node *populate, Node *parent, int step, int f_x, int f_y, char path): Takes the node given and
*     assigns the parameters.
*/
void populateNode(Node *populate, Node *parent, int step, int f_x, int f_y, char path)
{
	populate->parent = parent;
	populate->step = step;
	populate->g = heuristic(populate->x, populate->y, f_x, f_y, step);
	populate->path = path;
	return;
}


/*
* void markAsVisited(Node *node): Checks if the node is marked as visited, if not, adds
*     16 to the walls value of the node to mark as visited for the future reference
*/
void markAsVisited(Node *node)
{
	if (isVisited(node) == 0)
	{
		node->walls = node->walls + 16;
	}
	return;
}


/*
* isVisited(Node *node): returns 1 if the input Node is marked as visited (5th bit set high) otherwise, returns 0
*/
int isVisited(Node *node)
{
	if ((node->walls & 16) == 0)
	{
		return 0;
	}
	return 1;
}


/*
* int isFinish(Node *node, MazeData *md): returns 1 if the passed node has finish y and x position
*     otherwise, returns 0
*/
int isFinish(Node *node, MazeData *md)
{
	// Due to high number of iteration most of the time only one variable needs to be checked
	// If true checks the second one
	if (node->x == md->info[5])
	{
		if (node->y == md->info[4])
		{
			return 1;
		}
	}
	return 0;
}


/*
* void backtrackSolution(Node *node, MazeData *md): Creates a table of type char and populates
*     it with characters dependent on the path taken (ex. If chosen down character ‘D’ is saved).
*     Additionally, for displaying the path, adds 32 to the variable node->walls.
*/
void backtrackSolution(Node *node, MazeData *md)
{
	if (node == NULL || md == NULL)
	{
		printf("Error. Backtrack Solution requires both, node and MazeData.");
		return;
	}

	md->solutionL = node->step;
	md->solution = calloc(node->step+1, sizeof(char));

	// Checks parent until get to the start point with parent as NULL
	while (node->parent != NULL)
	{
		// Add 32 to mark as the path
		node->walls = node->walls + 32;
		md->solution[node->step] = node->path;
		node = node->parent;
	}
	return;
}


/*
* void algorithm_Test(): Function perform a series of automated tests to most of the functions
*     in the algorithm.h. Then displays the tests passed and failed in the console.
*     In case a test is failed displays the error message
*/
void algorithm_Test()
{
	// Testing Heuristic
	if (heuristic(-5, 15, 4, 4, 3) == 23)
	{
		printf("Test passed: 'int heuristics(...)'\n");
	}
	else
	{
		printf("Test failed: 'int heuristics(...)'\n");
	}

	// Testing populateNode
	Node *curNode = (Node*)malloc(sizeof(Node));
	curNode->x = 0;
	curNode->y = 0;
	populateNode(curNode, NULL, 0, 1, 1, 'L');
	if (curNode->parent == NULL && curNode->step == 0 && curNode->g == 2 && curNode->path == 'L')
	{
		printf("Test passed: 'void populateNode(...)'\n");
	}
	else
	{
		printf("Test failed: 'void populateNode(...)'\n");
	}

	// Testing isVisited
	curNode->walls = 0;
	if (isVisited(curNode))
	{
		printf("Test failed: 'int isVisited(Node *node)'\n");
	}
	else
	{
		printf("Test passed: 'void isVisited(Node *node)'\n");
	}

	// Testing markAsVisited
	markAsVisited(curNode);
	if (isVisited)
	{
		printf("Test passed: 'void markAsVisited(Node *node)'\n");
	}
	else
	{
		printf("Test failed: 'void markAsVisited(Node *node)'\n");
	}

	// Testing isFinished
	char* str = "mazeTest.txt";
	MazeData *d_test = readMaze(str);
	if (isFinish(curNode, d_test))
	{
		printf("Test failed: 'int isFinished(Node *node, MazeData *md)'\n");
	}
	else
	{
		printf("Test passed: 'int isFinished(Node *node, MazeData *md)'\n");
	}

	destroyMazeData(d_test);
	free(curNode);
	return;
}