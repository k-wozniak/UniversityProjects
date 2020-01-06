/*
 * mainFunctions.c
 *
 *  Created on: 11 Nov 2019
 */
#include "mainFunctions.h"

static int charToInt(char *input)
{
	char* p;
	long arg = strtol(input, &p, 10);

	if (*p != '\0')
	{
		return -1;
	}

	return (arg > INT_MIN && arg < INT_MAX) ? (int) arg : -1;
}

int mainSetup(int argc, char* argv[], ProcessInfo *info, int *threads, int *print)
{
	if (argc < 8)
	{
		printf("Too few arguments.\n");
		return -1;
	}


	for (int i = 1; i < argc; ++i) // i=1 ignore program name
	{
		if (strcmp(argv[i], "-a") == 0) // -a array
		{
			info->readArray = createArray(info->cols, info->rows);
			info->writeArray = createArray(info->cols, info->rows);

			// Copy each array element to the input array
			for (int row = 0; row < info->rows; row++)
			{
				for (int col = 0; col < info->cols; col++)
				{
					info->writeArray[row][col] = (double) atof(argv[++i]);
					info->readArray[row][col] = (double) atof(argv[i]);
				}
			}
		}
		else if (strcmp(argv[i], "-af") == 0) // array from file base on
		{
			FILE *fp = fopen(argv[++i], "r");
			double read;

			if (fp == NULL)
			{
				printf("File does not exist");
				return -1;
			}

			info->readArray = createArray(info->cols, info->rows);
			info->writeArray = createArray(info->cols, info->rows);

			// Copy each array element to the input array
			for (int row = 0; row < info->rows; row++)
			{
				for (int col = 0; col < info->cols; col++)
				{
					if(fscanf(fp, "%lf", &read) != EOF)
					{
						info->writeArray[row][col] = read;
						info->readArray[row][col] = read;
					}
					else
					{
						return -1;
					}
				}
			}
			fclose(fp);
		}
		else if (strcmp(argv[i], "-d") == 0) // dimensions
		{
			info->cols = charToInt(argv[++i]);
			info->rows = charToInt(argv[i]);

			if (info->rows < 3 || info->cols < 3)
			{
				printf(
						"Array dimensions must be positive integer "
						"larger than 0.\n");
				return -1;
			}
		}
		else if (strcmp(argv[i], "-t") == 0) // Number of threads
		{
			*threads = charToInt(argv[++i]);
		}
		else if (strcmp(argv[i], "-p") == 0) // Precision
		{
			info->precision = (double) atof(argv[++i]);
		}
		else if (strcmp(argv[i], "-print") == 0) // Prints array
		{
			*print = 1;
		}
		else if (strcmp(argv[i], "-h") == 0) // help
		{
			// Display manual and exit
			printf(
					"ProgramName usage:\n"
					"ProgramName -d [int] -t [int] -p [double] -a "
					"[double double ... double]\n\n"
					"Arguments:\n"
					"-af\t\t\tFile name to the 2D input array\n"
					"-d\t\t\tArray dimensions [int]\n"
					"-a\t\t\tInput 2D double array. Must be passed after\n"
					"-print\t\t\tPrints final array on the screen\n"
					"-t\t\t\tThreads number must be more than 0[int]\n"
					"-p\t\t\tPrecision the numbers will be estimated to\n"
					"[double], must be more than 0.\n"
					"-h\t\t\tHelp manual\n\n");
			return -1;
		}
		else // Something went wrong, ignore and leave the program
		{
			printf(
					"Unknown argument: \"%s\"\nMore info with \"ProgramName -h\"\n",
					argv[i]);
			return -1;
		}
	}

	// Test if every argument is correctly populated
	bool success = true;

	if (*threads < 1)
	{
		printf("Threads number must be a positive integer larger than 0.\n");
		success = false;
	}
	if (info->rows < 3 || info->cols < 3)
	{
		printf("Array dimensions must be positive integer larger than 0.\n");
		success = false;
	}
	if (info->readArray == NULL || info->writeArray == NULL)
	{
		printf("Unknown Error. Array pointers are null.\n");
		success = false;
	}
	if (info->precision <= 0)
	{
		printf("Precision must be positive integer larger than 0.\n");
		success = false;
	}

	if (success == false)
	{
		return -1;
	}

	return 0;
}

void getSegmentHeight(int *out_threads, int rows, int *out_height,
		int *out_remainder)
{
	rows = rows - 2;

	// If number of threads is bigger than rows decrease number of threads
	// No point over complicate and divide array in a bigger detail
	if (*out_threads >= rows)
	{
		*out_height = 1;
		*out_remainder = 0;
		*out_threads = rows;
	}
	else
	{
		*out_height = (rows / *out_threads);
		*out_remainder = (rows % *out_threads);
	}
}

void swapPointersArrays(double ***a, double ***b)
{
	double **temp = *a;
	*a = *b;
	*b = temp;
}

void destroyThreadRunners(ThreadRunner *threadRunners)
{
	free(threadRunners);
}

ThreadRunner *getThreadRunners(ProcessInfo *info, int threads, int remainder,
		int height)
{
	// Check if inputs makes sense
	if (threads < 1 || remainder < 0 || remainder >= threads || height < 1)
	{
		return NULL;
	}

	int r = (remainder > 0) ? 1 : 0;
	int s = 1;
	int f = height + r;

	ThreadRunner *threadRunners = (ThreadRunner*) calloc((unsigned) threads,
			sizeof(ThreadRunner));

	for (int i = 0; i < threads; i++, r--)
	{
		threadRunners[i].info = info;
		threadRunners[i].sRow = s;
		threadRunners[i].eRow = f;

		r = (--remainder > 0) ? 1 : 0;
		s = ++f;
		f = (s + height + r - 1);
	}

	return threadRunners;
}

int startThreads(ThreadRunner *threadRunners, pthread_t *threads, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (pthread_create(&threads[i], NULL, threadMain,
				(void*) &threadRunners[i]))
		{
			printf("Threads can't be created!");
			return -1;
		}
	}

	return 0;
}

// Main loop that controls child threads
void mainLoop(ProcessInfo *threadInfo)
{
	while (1)
	{
		// Wait until threads finish work
		pthread_barrier_wait(threadInfo->barrier);

		if (threadInfo->ready == 0)
		{
			pthread_mutex_lock(threadInfo->mutex);
			threadInfo->finish = 1;
			pthread_mutex_unlock(threadInfo->mutex);

			pthread_barrier_wait(threadInfo->barrier);
			return;
		}

		// Computation not ready, need continue
		// Swap arrays and reset data so threads can continue
		swapPointersArrays(&threadInfo->readArray, &threadInfo->writeArray);
		threadInfo->ready = 0;

		// Join with all threats so they can continue
		pthread_barrier_wait(threadInfo->barrier);
	}
}

void printArray(double **array, int rows, int cols)
{
	printf("\nOutput:\n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%lf\t", array[i][j]);
		}
		printf("\n");
	}
}
