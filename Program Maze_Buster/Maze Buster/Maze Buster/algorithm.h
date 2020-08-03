#pragma once
#include "storage.h"
#include "linkList.h"

// Functions Decelerations
MazeData *findMazeSolution(MazeData *md);
int heuristic(int c_x, int c_y, int f_x, int f_y, int step);
Node *returnNeighbour(int direction, Node *node, MazeData *md);
void populateNode(Node *populate, Node *parent, int step, int f_x, int f_y, char path);
void markAsVisited(Node *node);
int isVisited(Node *node);
int isFinish(Node *node, MazeData *md);
void backtrackSolution(Node *node, MazeData *md);
void algorithm_Test();