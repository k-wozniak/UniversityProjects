/*
 * Computation.h
 *
 *  Created on: 11 Nov 2019
 */

#ifndef COMPUTATION_H_INCLUDED
#define COMPUTATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/**
 * Computes Average for each cell in a column using its 4 neighbours
 * For each row beginning from startRow to endRow
 * columns - number of columns in the read and write Array
 * rows - number of rows in the read and write array
 * sRow - start Row (inclusive)
 * eRow - end row (inclusive)
 * readArr - array used to read the values
 * writeArr - array used to write the values
 * return - maximum difference between old and new value
 */
double computeAveragesForRows(int columns, int rows, int sRow, int eRow,
		double** readArr, double** wrtiteArr);

/**
 * Computes average of 4 values
 * a, b, c, d - input values
 * return - average value
 */
double computeAverageOfFour(double a, double b, double c, double d);

/**
 * Creates and allocates array
 * rows - number of rows
 * columns - number of columns
 * return pointer to 2D array
 */
double** createArray(int rows, int columns);

/**
 * Deallocates memory for 2D double array
 * arr - pointer to 2D array
 * rows - number of rows in the array
 */
void dealocateArray(double** arr, int rows);
#endif
