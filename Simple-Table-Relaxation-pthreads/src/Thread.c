/*
 * Thread.c
 *
 *  Created on: 11 Nov 2019
 */

#include "Thread.h"

void initialiseEmptyProcessInfo(ProcessInfo* info)
{
	info->cols = 0;
	info->rows = 0;
	info->precision = 0.1;
	info->readArray = NULL;
	info->writeArray = NULL;
	info->barrier = NULL;
	info->mutex = NULL;
	info->ready = 0;
	info->finish = 0;
}

static void wait(pthread_barrier_t *barr)
{
	int res = pthread_barrier_wait(barr);
	if (res != PTHREAD_BARRIER_SERIAL_THREAD && res != 0)
	{
		// error occurred something with p_threads
		printf("Wait! error occurred something with p_threads");
	}
}


 static void finishedLoop(pthread_barrier_t *barr, pthread_mutex_t *mutex,
		 int *finish)
 {
	// Computation completed, wait until the program is terminated
	while (true)
	{
		// The same as the normal thread worker
		wait(barr);
		wait(barr);

		pthread_mutex_lock(mutex);
		if (*finish == 1)
		{
			pthread_mutex_unlock(mutex);
			return;
		}
		pthread_mutex_unlock(mutex);
	}
 }

// TODO needs tests
void threadMainWorker(ProcessInfo *info, int sRow, int eRow)
{
	// Compute until precision is reached
	while (1)
	{
		double calculatedPrecision = computeAveragesForRows(info->cols,
				info->rows, sRow, eRow, info->readArray, info->writeArray);

		// Check if precision level reached
		if (info->precision >= calculatedPrecision)
		{
			return;
		}
		else
		{
			info->ready = 1;
			wait(info->barrier);
			// Allows the main thread to sync
			wait(info->barrier);
		}
	}
}

void *threadMain(void *threadRunner)
{
	// Start Variables
	ThreadRunner *tRunner = (ThreadRunner *) threadRunner;

	threadMainWorker(tRunner->info, tRunner->sRow, tRunner->eRow);

	finishedLoop(tRunner->info->barrier, tRunner->info->mutex,
			&tRunner->info->finish);

	return 0;
}
