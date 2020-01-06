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

	assert((info.cols == 0 && info.rows == 0),
			"Cols, Rows, Ready should be 0");
	assert((info.precision == 0.1), "Precision should be 0.1");
	assert((info.writeArr == NULL),
			"ReadArray, writeArray and barrier should be NULL");
}

bool runAllTests_threadTests()
{
	// Test initialiseEmptyThreadInfo
	initialiseEmptyThreadInfo_passEmpty_correctDataOut();

	// Finish Tests
	return (success == true);
}
