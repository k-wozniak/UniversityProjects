/*
 * Computation.c
 *
 *  Created on: 11 Nov 2019
 */

#include "Computation.h"

double computeAveragesForRows(int columns, int sRow, int eRow,
		double** readArr, double** wrtiteArr)
{
	if (columns < 3) // Computation not possible if less than 3 cols
	{
		return -1;
	}

	double maxDifference = -1;
	double difference = 0;
	double average = 0;

	// Go through each row between start and end
	for (int i = sRow; i <= eRow; i++)
	{
		// Go through the columns in the row and compute averages
		for (int j = 1; j < (columns - 1); j++)
		{
			average = computeAverageOfFour(readArr[i - 1][j], readArr[i][j - 1],
					readArr[i][j + 1], readArr[i + 1][j]);

			wrtiteArr[i][j] = average;

			difference = fabs(average - readArr[i][j]);

			maxDifference = (maxDifference < difference)
					? difference : maxDifference;
		}
	}

	return maxDifference;
}

double computeAverageOfFour(double a, double b, double c, double d)
{
	return ((a + b + c + d) / 4);
}

static size_t int2size_t(int val)
{
	return (val < 0) ? __SIZE_MAX__ : (size_t) ((unsigned) val);
}

double** createArray(int rows, int columns)
{
	size_t rows_t = int2size_t(rows);
	size_t columns_t = int2size_t(columns);

	double** arr = (double**) calloc(rows_t, sizeof(double*));

	for (int i = 0; i < rows; i++)
	{
		arr[i] = (double*) calloc(columns_t, sizeof(double));
	}

	return arr;
}

void dealocateArray(double** arr, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr);
}
