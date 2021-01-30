#pragma once
#include "storage.h"
#include "linkList.h"

/* Function: findMazeSolution
 * --------------------------
 * A* algorithm solving the maze
 * 
 * md: data structure with the maze
 * 
 * returns: mazeData with solution or NULL if error
 */
MazeData *findMazeSolution(MazeData *md);

/* Function: heuristic
 * -------------------
 * return heuristics of a current position (c_x & c_y) based on the Manhattan distance to the target and the current step
 *
 * c_x: current X position
 * c_y: current Y position
 * f_x: finish X position
 * f_y: finished Y position
 * step: Current step (added to the heuristics)
 *
 * returns: heuristics of a current position
 */
int heuristic(int c_x, int c_y, int f_x, int f_y, int step);

/* Function: returnNeighbour
 * -------------------------
 * return a pointer of the neighbor in the direction  given by the integer 'direction'
 * (1 - right, 2 - down, 4 - left, 8 - up). If neighbor does not exist returns NULL.
 *
 * direction: to search for (1 - right, 2 - down, 4 - left, 8 - up)
 * node: current node
 * md: Maze data structure
 *
 * return: a pointer of the neighbor
 */
Node *returnNeighbour(int direction, Node *node, MazeData *md);

/* Function: populateNode
 * ----------------------
 * Takes the node given and assigns the parameters.
 *
 * populate: Node to populate
 * parent: parent node
 * step: step at which it was reached
 * f_x: X position
 * f_y: Y position
 * path: Current path
 */
void populateNode(Node *populate, Node *parent, int step, int f_x, int f_y, char path);

/* Function: markAsVisited
 * -----------------------
 * Checks if the node is marked as visited, if not, adds 16 to the walls value of the node to 
 * mark as visited for the future reference
 *
 * node: node to mark as visited 
 */
void markAsVisited(Node *node);

/* Function: isVisited
 * -------------------
 * Checks if the node was visited
 *
 * node: node to check
 *
 * returns: 0 if false and 1 if true
 */
int isVisited(Node *node);

/* Function: isFinish
 * ------------------
 * Checks if the node is the finished node
 *
 * node: node to check
 * md: maze structure
 *
 * returns: 0 if false, 1 if true
 */
int isFinish(Node *node, MazeData *md);

/* Function: backtrackSolution
 * ---------------------------
 * Creates a table of type char and populates it with characters dependent on the path taken
 * (ex. If chosen down character ‘D’ is saved). Additionally, for displaying the path, adds 32 to the variable node->walls.
 *
 * node: starting node
 * md: maze data
 */
void backtrackSolution(Node *node, MazeData *md);

/* Function: algorithm_Test
 * ------------------------
 * <What it does>
 */
void algorithm_Test();