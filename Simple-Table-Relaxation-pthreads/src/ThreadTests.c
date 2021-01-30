/*
 * ThreadTests.c
 *
 *  Created on: 11 Nov 2019
 */

#include "ThreadTests.h"

static bool success = true;

static void assert(bool condition, char testName[])
{
	if (condition == false)
	{
		success = false;
		printf("Test Failed. %s\n", testName);
	}
}

/*
 * Test initialiseEmptyThreadInfo(ThreadInfo * info)
 */
static void initialiseEmptyThreadInfo_passEmpty_correctDataOut()
{
	ProcessInfo info;
	initialiseEmptyProcessInfo(&info);

	assert((info.cols == 0 && info.rows == 0 && info.ready == 0),
			"Cols, Rows, Ready should be 0");
	assert((info.precision == 0.1), "Precision should be 0.1");
	assert(
			(info.readArray == NULL && info.writeArray == NULL
					&& info.barrier == NULL),
			"ReadArray, writeArray and barrier should be NULL");
}

/*
 * Test threadMainWorker(ThreadInfo *info, int sRow, int eRow)
 */
static void threadMainWorker_smallArray_5x5_OnePass_CorrectOutput1()
{
	ProcessInfo info;
	info.cols = 5;
	info.rows = 5;
	info.precision = 0.1;
	info.ready = 0;
	info.readArray = createArray(5, 5);
	info.writeArray = createArray(5, 5);

	pthread_barrier_t actual_barrier;
	info.barrier = &actual_barrier;
	pthread_barrier_init(info.barrier, NULL, 1);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int value = i + j;
			info.readArray[i][j] = value;
			info.writeArray[i][j] = value;
		}
	}

	threadMainWorker(&info, 1, 3);

	bool s = true;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int value = i + j;
			s = (info.writeArray[i][j] == value);
		}
	}
	assert(s, "Incorrect Averages");

	pthread_barrier_destroy(info.barrier);
	dealocateArray(info.readArray, 5);
	dealocateArray(info.writeArray, 5);
}

static void threadMainWorker_smallArray_5x5_OnePass_CorrectOutput2()
{
	ProcessInfo info;
	info.cols = 5;
	info.rows = 5;
	info.precision = 5;
	info.ready = 0;
	info.readArray = createArray(5, 5);
	info.writeArray = createArray(5, 5);

	pthread_barrier_t actual_barrier;
	info.barrier = &actual_barrier;
	pthread_barrier_init(info.barrier, NULL, 1);

	int list[25] = { 0, 4, 4, 4, 0, 4, 0, 0, 0, 4, 4, 0, 0, 0, 4, 4, 0, 0, 0, 4,
			0, 4, 4, 4, 0 };
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int value = list[(i * 5) + j];
			info.readArray[i][j] = value;
			info.writeArray[i][j] = value;
		}
	}

	threadMainWorker(&info, 1, 3);
	assert(info.writeArray[1][1] == 2, "Incorrect Averages");
	assert(info.writeArray[1][2] == 1, "Incorrect Averages");
	assert(info.writeArray[1][3] == 2, "Incorrect Averages");
	assert(info.writeArray[2][1] == 1, "Incorrect Averages");
	assert(info.writeArray[2][2] == 0, "Incorrect Averages");
	assert(info.writeArray[2][3] == 1, "Incorrect Averages");
	assert(info.writeArray[3][1] == 2, "Incorrect Averages");
	assert(info.writeArray[3][2] == 1, "Incorrect Averages");
	assert(info.writeArray[3][3] == 2, "Incorrect Averages");

	pthread_barrier_destroy(info.barrier);
	dealocateArray(info.readArray, 5);
	dealocateArray(info.writeArray, 5);
}

static void threadMainWorker_smallArray_5x5_OnePass_CorrectOutput3()
{
	ProcessInfo info;
	info.cols = 5;
	info.rows = 5;
	info.precision = 20;
	info.ready = 0;
	info.readArray = createArray(5, 5);
	info.writeArray = createArray(5, 5);

	pthread_barrier_t actual_barrier;
	info.barrier = &actual_barrier;
	pthread_barrier_init(info.barrier, NULL, 1);

	int list[25] = { 0, 2, 5, 7, 9, 3, 8, 1, 2, 5, 4, 2, 9, 1, 1, 5, 4, 8, 2, 3,
			0, 2, 2, 5, 0 };
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int value = list[(i * 5) + j];
			info.readArray[i][j] = value;
			info.writeArray[i][j] = value;
		}
	}

	threadMainWorker(&info, 1, 3);
	assert(info.writeArray[1][1] == 2, "Incorrect Averages [1][1]");
	assert(info.writeArray[1][2] == 6, "Incorrect Averages [1][2]");
	assert(info.writeArray[1][3] == 3.5, "Incorrect Averages [1][3]");
	assert(info.writeArray[2][1] == 6.25, "Incorrect Averages [2][1]");
	assert(info.writeArray[2][2] == 3, "Incorrect Averages [2][2]");
	assert(info.writeArray[2][3] == 3.5, "Incorrect Averages [2][3]");
	assert(info.writeArray[3][1] == 4.25, "Incorrect Averages [3][1]");
	assert(info.writeArray[3][2] == 4.25, "Incorrect Averages [3][2]");
	assert(info.writeArray[3][3] == 4.25, "Incorrect Averages [3][3]");

	pthread_barrier_destroy(info.barrier);
	dealocateArray(info.readArray, 5);
	dealocateArray(info.writeArray, 5);
}

bool runAllTests_threadTests()
{
	// Test initialiseEmptyThreadInfo
	initialiseEmptyThreadInfo_passEmpty_correctDataOut();

	// Test threadMainWorker
	threadMainWorker_smallArray_5x5_OnePass_CorrectOutput1();
	threadMainWorker_smallArray_5x5_OnePass_CorrectOutput2();
	threadMainWorker_smallArray_5x5_OnePass_CorrectOutput3();

	// Finish Tests
	return (success == true);
}
