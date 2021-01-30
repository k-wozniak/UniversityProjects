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
	// Array that data will be read/write from
	double **readArr, **writeArr;

	// Number of rows and columns the readArray & writeArray consists of
	int rows, cols;

	// The precision number that the calculations will
	// continue until it is met for each array cell
	double precision;

	int numProcs, rank;
	bool print;
} ProcessInfo;

/**
 * Function that takes ThreadInfo and put initial values in
 */
void initialiseEmptyProcessInfo(ProcessInfo* info);

#endif /* THREAD_H_ */
