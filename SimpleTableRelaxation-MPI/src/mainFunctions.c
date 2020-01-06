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

int mainSetup(int argc, char* argv[], ProcessInfo *info)
{
	for (int i = 1; i < argc; ++i) // i=1 ignore program name
	{
		if (strcmp(argv[i], "-testArray") == 0) // test array with just border
		{
			info->cols = charToInt(argv[++i]);
			info->rows = charToInt(argv[i]);

			double borderValue = (double) atof(argv[++i]);

			// Find the start, end and height of the segment for this rank
			info->rows = getSegmentHeight(info->rank, info->numProcs, info->rows);
			if(info->rows == 0)
			{
				printf("Not enough rows for number of processes!\n");
				return -1;
			}

			info->readArr = createArray(info->rows, info->cols);
			info->writeArr = createArray(info->rows, info->cols);

			// Copy each array element to the input array
			for (int row = 0; row < info->rows; row++)
			{
				info->readArr[row][0] = borderValue;
				info->readArr[row][info->cols-1] = borderValue;

				info->writeArr[row][0] = borderValue;
				info->writeArr[row][info->cols-1] = borderValue;
			}

			if(info->rank == 0)
			{
				for(int col = 0; col < info->cols - 1; col++)
				{
					info->readArr[0][col] = borderValue;
					info->writeArr[0][col] = borderValue;
				}
			}

			if(info->rank == (info->numProcs-1))
			{
				for(int col = 0; col < info->cols-1; col++)
				{
					info->readArr[info->rows-1][col] = borderValue;
					info->writeArr[info->rows-1][col] = borderValue;
				}
			}
		}
		else if (strcmp(argv[i], "-p") == 0) // Precision
		{
			info->precision = (double) atof(argv[++i]);
		}
		else if (strcmp(argv[i], "-print") == 0) // Prints array
		{
			info->print = true;
		}
		else // Something went wrong, ignore and leave the program
		{
			// Display manual and exit
			printf(
					"ParallelOpenMPI usage:\n"
					"ParallelOpenMPI -p [double] -testArray size[int] bVal[int]"
					"\n\n"
					"Arguments:\n"
					"-testArray [int] [int]\t\t\tSize and initial border value\n"
					"-print\t\t\tPrints final array on the screen\n"
					"-p\t\t\tPrecision the numbers will be estimated to\n"
					"[double], must be more than 0.\n");
			return -1;
		}
	}

	// Test if every argument is correctly populated
	bool success = true;
	if (info->rows < 3 || info->cols < 3)
	{
		printf("Array dimensions must be positive integer larger than 0.\n");
		success = false;
	}
	if (info->writeArr == NULL || info->readArr == NULL)
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

int getSegmentHeight(int rank, int processesNum, int totalRows)
{
	// First & last row are constant so excluded from calculations
	totalRows = totalRows - 2;

	// If number of rows does not allow for each process to have at least
	// 2 computation rows then return 0 as it will exit the program
	if ( (processesNum*2) > totalRows)
	{
		return 0;
	}

	// To make each segment as similar as possible, segment height is
	// number of rows divided by number of processes
	int height = (totalRows / processesNum);

	// Gets the number of rows not distributed between processes if not
	// perfectly divided
	int remainder = (totalRows % processesNum);

	// To the existing height add two as for the constant/received
	// top and bottom row.
	height += 2;

	// If rank is lower than the remainder given segment should have one more
	// row
	height += (remainder > rank) ? 1 : 0;

	return height;
}

void printArray(double **array, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%lf\t", array[i][j]);
		}
		printf("\n");
	}
}

void swapPointersArrays(double ***a, double ***b)
{
	double **temp = *a;
	*a = *b;
	*b = temp;
}
