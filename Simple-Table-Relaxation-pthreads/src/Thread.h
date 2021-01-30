/*
 * Thread.h
 *
 *  Created on: 11 Nov 2019
 */

#ifndef THREAD_H_
#define THREAD_H_

#define _GNU_SOURCE

#include <pthread.h>
#include <stdbool.h>
#include "Computation.h"

/* Prototypes for the functions */
typedef struct _ProcessInfo
{
	// Array that data will be read from
	// The Thread WILL NOT MODIFY the data
	double** readArray;

	// Array that data will be write into
	// The Thread WILL MODIFY the data in range given
	double** writeArray;

	// Number of rows and columns the readArray & writeArray consists of
	int rows, cols;

	// The precision number that the calculations will
	// continue until it is met for each array cell
	double precision;

	// Used to sync threads
	pthread_barrier_t* barrier;
	int ready; // Set to zero if threads are ready, one if any thread is not ready
	pthread_mutex_t *mutex;
	int finish;

} ProcessInfo;

typedef struct _ThreadRunner
{
	ProcessInfo *info; // Constant info, shared between threads
	int sRow; // Start row for a given thread
	int eRow; // End row for a given thread

} ThreadRunner;

/**
 *	Start point of the thread
 */
void *threadMain(void *threadRunner);

/**
 * Function that takes ThreadInfo and put initial values in
 */
void initialiseEmptyProcessInfo(ProcessInfo* info);

/**
 * threadMain calls threadMainWorker after getting all needed values
 * then threadMainWorker in a loop goes through given rows and columns and
 * performs calculations
 * info - all required information for the thread
 * sRow - start row
 * eRow - end row
 */
void threadMainWorker(ProcessInfo *info, int sRow, int eRow);

#endif /* THREAD_H_ */
