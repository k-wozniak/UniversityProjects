/*
 *  mainFunctions.c
 *
 *  Created on: 11 Nov 2019
 */

#ifndef MAIN_FUNCTIONS_C_
#define MAIN_FUNCTIONS_C_

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>

#include "Thread.h"
#include "Computation.h"

/**
 * Takes programs input arguments and converts them into usable
 * internal structure
 * return error code 0 - everything all right
 */
int mainSetup(int argc, char* argv[], ProcessInfo *info);

/**
 * Calculates the number of rows for a given segment
 * rank - rank of the process
 * processesNum - number of processes
 * totalRows - total number of rows
 */
int getSegmentHeight(int rank, int processesNum, int totalRows);

/**
 * Prints array to the serial out
 */
void printArray(double **array, int rows, int cols);


/**
 * Swaps addresses to which the pointers point to
 */
void swapPointersArrays(double ***a, double ***b);

#endif /* MAIN_FUNCTIONS_C_ */
