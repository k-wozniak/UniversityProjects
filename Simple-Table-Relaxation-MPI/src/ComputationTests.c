/*
 * ComputationTests.c
 *
 *  Created on: 11 Nov 2019
 */

#include "ComputationTests.h"

static bool success = true;

static void failed(char testName[])
{
	success = false;
	printf("Test Failed. %s\n", testName);
}

/*
 * TestComputeAverageOfFour
 */
void test_computeAverageOfFour_inputTheSameDouble_expectTheSameOutput()
{
	double a = 5.0, b = 5.0, c = 5.0, d = 5.0;
	double expectedOut = 5;

	double out = computeAverageOfFour(a, b, c, d);

	if (expectedOut != out)
	{
		failed("Failed Test test computeAverageOfFour "
				"inputTheSameDouble expectTheSameOutput");
	}
}

void test_computeAverageOfFour_inputNegativeNumer_expectCorrectOutput()
{
	double a = -5.0, b = -5.0, c = -5.0, d = 5.0;
	double expectedOut = (-2.5);

	double out = computeAverageOfFour(a, b, c, d);

	if (expectedOut != out)
	{
		failed("Failed Test test computeAverageOfFour inputTheSameDouble "
				"expectTheSameOutput");
	}
}

void test_computeAverageOfFour_allZeros_expectZero()
{
	double a = 0.0, b = 0.0, c = 0.0, d = 0.0;
	double expectedOut = (0.0);

	double out = computeAverageOfFour(a, b, c, d);

	if (expectedOut != out)
	{
		failed("Failed Test computeAverageOfFour inputTheSameDouble "
				"expectTheSameOutput");
	}
}

/*
 * Test computeAveragesForARow
 */
void test_createArrayAnddealocateArray()
{
	int rows = 3, col = 4;
	double** arr = createArray(rows, col);

	// check if all zeros
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (arr[i][j] != 0)
			{
				failed("Not Zero");
				dealocateArray(arr, rows);
				return;
			}
		}
	}

	// write
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int value = (i * col) + j;
			arr[i][j] = value;
		}
	}

	// read out
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
#ifdef WIN32
#pragma warning (disable: 26451)  //It wont overflow and its a tests
			if (arr[i][j] != ((i * col) + j))
			{
				failed("Incorrect number!");
				dealocateArray(arr, rows);
				return;
			}
#endif
		}
	}

	dealocateArray(arr, rows);
}

/*
 * Test computeAveragesForARow
 */
void test_computeAveragesForARow_inputIncreasingArray_expectCorrectOutput()
{
	int rows = 3, col = 4;
	double** read = createArray(rows, col);
	double** write = createArray(rows, col);

	// write
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int value = (i * col) + j;
			read[i][j] = value;
		}
	}

	computeAveragesForRows(col, 1, 1, read, write);

	// read out
	if (write[1][1] != 5 || write[1][2] != 6)
	{
		failed("Incorrect averages!");
	}

	dealocateArray(read, rows);
	dealocateArray(write, rows);
}

void test_computeAveragesForARow_inputArrayWithTheSameData_expectCorrectOutput()
{
	int rows = 3, col = 3;
	double** read = createArray(rows, col);
	double** write = createArray(rows, col);

	// write 5 to each cell
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			read[i][j] = 5;
		}
	}

	computeAveragesForRows(col, 1, 1, read, write);

	// read out
	if (write[1][1] != 5)
	{
		failed("test computeAveragesForARow inputArrayWithTheSameData "
				"expectCorrectOutput: Incorrect averages");
	}

	dealocateArray(read, rows);
	dealocateArray(write, rows);
}

void test_computeAveragesForARow_inputTooSmallArray_expectReturnNoProcessing()
{
	int rows = 3, col = 2;
	double** read = createArray(rows, col);
	double** write = createArray(rows, col);

	// write 5 to each cell
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			read[i][j] = 5;
		}
	}

	double a = computeAveragesForRows(col, 1, 1, read, write);

	if (a != (-1))
	{
		failed("Compute Edited Variables");
	}

	dealocateArray(read, rows);
	dealocateArray(write, rows);
}

bool runAllTests_computationTests()
{
	// Tests ComputeAverageOfFour
	test_computeAverageOfFour_inputTheSameDouble_expectTheSameOutput();
	test_computeAverageOfFour_inputNegativeNumer_expectCorrectOutput();
	test_computeAverageOfFour_allZeros_expectZero();

	// Test createArray & dealocateArray
	test_createArrayAnddealocateArray();

	// Tests computeAveragesForARow
	test_computeAveragesForARow_inputIncreasingArray_expectCorrectOutput();
	test_computeAveragesForARow_inputArrayWithTheSameData_expectCorrectOutput();
	test_computeAveragesForARow_inputTooSmallArray_expectReturnNoProcessing();

	// Finish Tests
	return (success == true);
}