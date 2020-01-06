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
int mainSetup(int argc, char* argv[], ProcessInfo *info, int *threads, int *print);

/**
 * Calculates informations required to divide array into rows
 * arguments marked as out_ are output
 * out_threads - number of threads, if larger than number of rows it will be
 * 		scaled down
 * rows - number of rows
 * out_height - segment height in rows
 * out_remainder - number of rows left after division
 */
void getSegmentHeight(int *out_threads, int rows, int *out_height,
		int *out_remainder);

/**
 * Swaps addresses to which the pointers point to
 */
void swapPointersArrays(double ***a, double ***b);

/**
 * Allocate memory for a given number of struct ThreadRunner
 */
ThreadRunner *createThreadRunners(int count);

/**
 * Deallocates memory for ThreadRunners
 */
void destroyThreadRunners(ThreadRunner *threadRunners);

/**
 * Populates thread runners for the given program information, number of threads
 * 		, height of a segment and remainder
 * return - populated ThreadRunner structures
 */
ThreadRunner *getThreadRunners(ProcessInfo *info, int threads, int remainder,
		int height);

/**
 * Start threads
 * ThreadRunners - structures required to run threads
 * *threads - array of pointers to threads
 * count - number of threads and threadrunners
 * return 0 is success and -1 if failure
 */
int startThreads(ThreadRunner *threadRunners, pthread_t *threads, int count);

/**
 * Main loop of the coordinator thread
 * main responsibility is to swap pointers after each thread iteration
 * and allow safe program exit
 */
void mainLoop(ProcessInfo *threadInfo);

/**
 * Prints array to the serial out
 */
void printArray(double **array, int rows, int cols);

#endif /* MAIN_FUNCTIONS_C_ */
