/*
 * IntegrationTests.c
 *
 *  Created on: 15 Nov 2019
 */
#include "IntegrationTests.h"

static bool success = true;

static void assert(bool condition, char testName[])
{
       if (condition == false)
       {
               success = false;
               printf("Test Failed. %s\n", testName);
       }
}

static double ** _main(int argc, char* argv[])
{
	// Create and populate the structure
		ProcessInfo threadInfo;
		initialiseEmptyProcessInfo(&threadInfo);

		int threadsNumber = 0, print = 0;

		int success = mainSetup(argc, argv, &threadInfo, &threadsNumber, &print);
		if (success != 0)
		{
			return NULL;
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
			return NULL;
		}

		// operation loop
		mainLoop(&threadInfo);

		// Print computation
		//printArray(threadInfo.writeArray, threadInfo.rows, threadInfo.cols);

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
		free(threads);
		pthread_barrier_destroy(&barrier);
		pthread_mutex_destroy(&mutex);

		return threadInfo.writeArray;
}

static void oneCore_8x8_maxPrecision()
{
       char *ARGV[] = {
                       "ProgramName", "-d", "8", "-t", "1", "-p", "0.00001", "-a", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
       };

       int ARGC = (int)((sizeof(ARGV) / sizeof(char*)) - 1);

       double **array = _main(ARGC, ARGV);

       for(int i = 0; i < 8; i++)
       {
               for(int j = 0; j < 8; j++)
               {
                       double a = array[i][j];
                       double difference = 5.00000 - a;
                       difference = (difference < 0) ? -difference : difference;
                       assert( difference <= 0.0001, "Did not approached 5 d = %d, program not working correctly!");
               }
       }

       dealocateArray(array, 8);
}

static void twoCore_8x8_maxPrecision()
{
       char *ARGV[] = {
                       "ProgramName", "-d", "8", "-t", "2", "-p", "0.00001", "-a", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
       };

       int ARGC = (int)((sizeof(ARGV) / sizeof(char*)) - 1);

       double **array = _main(ARGC, ARGV);

       for(int i = 0; i < 8; i++)
       {
               for(int j = 0; j < 8; j++)
               {
                       double a = array[i][j];
                       double difference = 5.00000 - a;
                       difference = (difference < 0) ? -difference : difference;
                       assert( difference <= 0.0001, "Did not approached 5 d = %d, program not working correctly!");
               }
       }

       dealocateArray(array, 8);
}

static void fourCore_8x8_maxPrecision()
{
       char *ARGV[] = {
                       "ProgramName", "-d", "8", "-t", "4", "-p", "0.00001", "-a", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
       };

       int ARGC = (int)((sizeof(ARGV) / sizeof(char*)) - 1);

       double **array = _main(ARGC, ARGV);

       for(int i = 0; i < 8; i++)
       {
               for(int j = 0; j < 8; j++)
               {
                       double a = array[i][j];
                       double difference = 5.00000 - a;
                       difference = (difference < 0) ? -difference : difference;
                       assert( difference <= 0.001, "Did not approached 5 d = %d, program not working correctly!");
               }
       }

       dealocateArray(array, 8);
}

static void sixCore_8x8_maxPrecision()
{
       char *ARGV[] = {
                       "ProgramName", "-d", "8", "-t", "6", "-p", "0.00001", "-a", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
       };

       int ARGC = (int)((sizeof(ARGV) / sizeof(char*)) - 1);

       double **array = _main(ARGC, ARGV);

       for(int i = 0; i < 8; i++)
       {
               for(int j = 0; j < 8; j++)
               {
                       double a = array[i][j];
                       double difference = 5.00000 - a;
                       difference = (difference < 0) ? -difference : difference;
                       assert( difference <= 0.001, "Did not approached 5 d = %d, program not working correctly!");
               }
       }

       dealocateArray(array, 8);
}

static void eightCore_putToSix_8x8_maxPrecision()
{
       char *ARGV[] = {
                       "ProgramName", "-d", "8", "-t", "8", "-p", "0.00001", "-a", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "0", "0", "0", "0", "0", "0", "5", \
                       "5", "5", "5", "5", "5", "5", "5", "5", \
       };

       int ARGC = (int)((sizeof(ARGV) / sizeof(char*)) - 1);

       double **array = _main(ARGC, ARGV);

       for(int i = 0; i < 8; i++)
       {
               for(int j = 0; j < 8; j++)
               {
                       double a = array[i][j];
                       double difference = 5.00000 - a;
                       difference = (difference < 0) ? -difference : difference;
                       assert( difference <= 0.001, "Did not approached 5 d = %d, program not working correctly!");
               }
       }

       dealocateArray(array, 8);
}

bool runIntegrationTests()
{
       oneCore_8x8_maxPrecision();
       twoCore_8x8_maxPrecision();
       fourCore_8x8_maxPrecision();
       sixCore_8x8_maxPrecision();
       eightCore_putToSix_8x8_maxPrecision();

       return success;
}

