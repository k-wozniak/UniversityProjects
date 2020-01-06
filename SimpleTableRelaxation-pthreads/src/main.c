/*
 * main.c
 *
 *  Created on: 11 Nov 2019
 */

#define HAVE_STRUCT_TIMESPEC
#define _TIMESPEC_DEFINED

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#include "mainFunctions.h"
#include "Thread.h"
#include "Computation.h"

#ifdef UNIT_TESTS
#include "Tests.h"
#endif

// Main Program Start
int main(int argc, char* argv[])
{

	// Runs unit tests but are excluded in release build
#ifdef UNIT_TESTS
	runAllTests();
#endif

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);

	int threadsNumber = 0, print = 0;

	int success = mainSetup(argc, argv, &threadInfo, &threadsNumber, &print);
	if (success != 0)
	{
		return -1;
	}

	// Algorithm to divide array to equal portions
	int rowHeight = 0, rowRemainder = 0;
	getSegmentHeight(&threadsNumber, threadInfo.rows, &rowHeight, &rowRemainder);

	// Create barrier
	pthread_barrier_t barrier;
	threadInfo.barrier = &barrier;
	pthread_barrier_init(&barrier, NULL, (unsigned) (threadsNumber + 1));

	// Create mutex
	pthread_mutex_t mutex;
	threadInfo.mutex = &mutex;
	pthread_mutex_init(&mutex, NULL);

	// start threads loop
	ThreadRunner *threadRunners = getThreadRunners(&threadInfo, threadsNumber,
			rowRemainder, rowHeight);
	pthread_t *threads = (pthread_t*) calloc((unsigned) threadsNumber,
			sizeof(pthread_t));
	success = startThreads(threadRunners, threads, threadsNumber);
	if (success != 0)
	{
		return -1;
	}

	// operation loop
	mainLoop(&threadInfo);

	// Print computation
	if(print == 1)
	{
		printArray(threadInfo.writeArray, threadInfo.rows, threadInfo.cols);
	}

#ifdef UNIT_TESTS
	// Wait for all threads to definitely end
	// Not in the Release mode as it is preferred to end program with not
	// Properly realised resources rather than stuck in a infinite loop
	// In case a thread stopped at a barrier
	for(int i = 0; i < threadsNumber; i++)
	{
		pthread_join(threads[i], NULL);
	}
#endif

	// clean-up
	dealocateArray(threadInfo.readArray, threadInfo.rows);
	dealocateArray(threadInfo.writeArray, threadInfo.rows);
	free(threads);
	pthread_barrier_destroy(&barrier);
	pthread_mutex_destroy(&mutex);

	// Exit
	return 0;
}
