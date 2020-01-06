/*
 *  mainFunctionsTests.c
 *
 *  Created on: 11 Nov 2019
 */

#include "mainFunctionsTests.h"

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
 * mainSetup
 */
static void mainSetup_correctInput_correctOutput()
{
	int argc = 18, threads = -1, print = 0;
	char* argv[] = { "ProgramName", "-d", "3", "-a", "1", "2", "3", "4", "5",
			"6", "7", "8", "9", "-t", "1", "-p", "0.01", "-print" };

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);

	int out = mainSetup(argc, argv, &threadInfo, &threads, &print);

	assert((out != -1), "Something went wrong with input, returned -1");

	assert((threads == 1), "Incorrect thread number");

	assert((threadInfo.cols == 3 && threadInfo.rows == 3),
			"Incorrect row/column number");

	assert((threadInfo.precision == 0.01), "Incorrect precision");

	assert((print == 1), "Print is not enabled.");

	assert((threadInfo.readArray != NULL && threadInfo.writeArray != NULL),
			"Read or Write array are null");

	dealocateArray(threadInfo.readArray, threadInfo.rows);
	dealocateArray(threadInfo.writeArray, threadInfo.rows);
}

static void mainSetup_arrayFileIn_correctOut()
{
	// Generate file
	FILE * fPtr = fopen("TestFileArray", "w");
	if(fPtr == NULL) { assert(false, "Unable to create file.\n"); }
	fputs("5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1", fPtr);
	fclose(fPtr);

	char* argv[] = { "ProgramName", "-d", "5", "-af", "TestFileArray", "-t", "1", "-p", "0.01" };

	int argc = 9, threads = -1, print = 0;
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);

	int out = mainSetup(argc, argv, &threadInfo, &threads, &print);

	assert((out != -1), "Something went wrong with input, returned -1");

	int v = 5;
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			assert((threadInfo.readArray[i][j] == v), "Incorrect read from file!");
		}
		v--;
	}

	remove("TestFileArray");
}

static void mainSetup_tooSmallArray_ErrorOutput()
{
	int argc = 17, threads = -1, print = 0;
	char* argv[] = { "ProgramName", "-d", "2", "-a", "1", "2", "3", "4", "5",
			"6", "7", "8", "9", "-t", "1", "-p", "0.01" };

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);

	int out = mainSetup(argc, argv, &threadInfo, &threads, &print);

	assert((out == -1), "Not corrected output.");
}

static void mainSetup_tooZeroThreads_ErrorOutput()
{
	int argc = 17, threads = -1, print = 0;
	char* argv[] = { "ProgramName", "-d", "3", "-a", "1", "2", "3", "4", "5",
			"6", "7", "8", "9", "-t", "0", "-p", "0.01" };

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);

	int out = mainSetup(argc, argv, &threadInfo, &threads, &print);

	assert((out == -1), "Not corrected output.");

	dealocateArray(threadInfo.readArray, threadInfo.rows);
	dealocateArray(threadInfo.writeArray, threadInfo.rows);
}

static void mainSetup_tooZeroPrecison_ErrorOutput()
{
	int argc = 17, threads = -1, print = 0;
	char* argv[] = { "ProgramName", "-d", "3", "-a", "1", "2", "3", "4", "5",
			"6", "7", "8", "9", "-t", "3", "-p", "0.00" };

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);

	int out = mainSetup(argc, argv, &threadInfo, &threads, &print);

	assert((out == -1), "Not corrected output.");

	dealocateArray(threadInfo.readArray, threadInfo.rows);
	dealocateArray(threadInfo.writeArray, threadInfo.rows);
}

/*
 * coefficients
 */
static void coefficients_correctIn_correctOut()
{
	int threads = 5, rows = 7, outH = 0, outR = 0;

	getSegmentHeight(&threads, rows, &outH, &outR);

	assert(threads == 5, "Threads has changed.");
	assert(rows == 7, "Rows has changed.");
	assert(outH == 1, "Incorrect Height");
	assert(outR == 0, "Incorrect R");
}

static void coefficients_lessThreadsThanRows_correctDevide()
{
	int threads = 5, rows = 22, outH = 0, outR = 0;

	getSegmentHeight(&threads, rows, &outH, &outR);

	assert(threads == 5, "Threads has changed.");
	assert(outH == 4, "Incorrect Height");
	assert(outR == 0, "Incorrect R");
}

static void coefficients_moreThreadsThanRows_correctDevide()
{
	int threads = 50, rows = 22, outH = 0, outR = 0;

	getSegmentHeight(&threads, rows, &outH, &outR);

	assert(threads == 20, "Threads has changed.");
	assert(outH == 1, "Incorrect Height");
	assert(outR == 0, "Incorrect R");
}

static void coefficients_unevenThreadsToColumnsRetio()
{
	int threads = 10, rows = 17, outH = 0, outR = 0;

	getSegmentHeight(&threads, rows, &outH, &outR);

	assert(threads == 10, "Threads has changed.");
	assert(outH == 1, "Incorrect Height");
	assert(outR == 5, "Incorrect R");
}

/*
 * swapPointersArrays
 */
static void swapPointersArrays_simpleSwap()
{
	double **a = createArray(5, 5);
	double **b = createArray(5, 5);

	double **aa = a;
	double **bb = b;

	assert(a == aa && b == bb, "Incorrect assignment");

	swapPointersArrays(&a, &b);

	assert(a == bb && b == aa && a != b, "Incorrect swap");

	dealocateArray(a, 5);
	dealocateArray(b, 5);
}

/*
 * getThreadRunners
 */
static void getThreadRunners_correctIn()
{
	int threads = 2, remainder = 0, height = 2;

	ThreadRunner *trs = getThreadRunners(NULL, threads, remainder, height);

	assert(trs[0].info == NULL, "0 Not null");
	assert(trs[1].info == NULL, "1 Not null");

	assert(trs[0].sRow == 1, "Not 1");
	assert(trs[1].sRow == 3, "Not 3");

	assert(trs[0].eRow == 2, "Not 2");
	assert(trs[1].eRow == 4, "Not 4");

	free(trs);
}

static void getThreadRunners_correctInWithRemainder()
{
	int threads = 3, remainder = 2, height = 5;

	ThreadRunner *trs = getThreadRunners(NULL, threads, remainder, height);

	assert(trs[0].info == NULL, "0 Not null");
	assert(trs[0].sRow == 1, "Not 1");
	assert(trs[0].eRow == 6, "Not 6");

	assert(trs[1].info == NULL, "1 Not null");
	assert(trs[1].sRow == 7, "Not 7");
	assert(trs[1].eRow == 12, "Not 12");

	assert(trs[2].info == NULL, "1 Not null");
	assert(trs[2].sRow == 13, "Not 13");
	assert(trs[2].eRow == 17, "Not 17");

	free(trs);
}

static void getThreadRunners_incorrectThreads()
{
	int threads = -5, remainder = 2, height = 5;

	ThreadRunner *trs = getThreadRunners(NULL, threads, remainder, height);

	assert(trs == NULL, "Pointer is not null");
}

static void getThreadRunners_incorrectRemainder()
{
	int threads = 5, remainder = -2, height = 5;

	ThreadRunner *trs = getThreadRunners(NULL, threads, remainder, height);
	assert(trs == NULL, "Pointer is not null");

	remainder = 10;
	trs = getThreadRunners(NULL, threads, remainder, height);
	assert(trs == NULL, "Pointer is not null");
}

static void getThreadRunners_incorrectHeight()
{
	int threads = 5, remainder = 2, height = -5;

	ThreadRunner *trs = getThreadRunners(NULL, threads, remainder, height);

	assert(trs == NULL, "Pointer is not null");
}

bool runAllTests_mainFunctionsTests()
{
	// Test mainSetup
	mainSetup_arrayFileIn_correctOut();
	mainSetup_correctInput_correctOutput();
	mainSetup_tooSmallArray_ErrorOutput();
	mainSetup_tooZeroThreads_ErrorOutput();
	mainSetup_tooZeroPrecison_ErrorOutput();

	// Test coefficients
	coefficients_correctIn_correctOut();
	coefficients_lessThreadsThanRows_correctDevide();
	coefficients_moreThreadsThanRows_correctDevide();
	coefficients_unevenThreadsToColumnsRetio();

	// Test swapPointersArrays
	swapPointersArrays_simpleSwap();

	// Test getThreadRunners
	getThreadRunners_correctIn();
	getThreadRunners_correctInWithRemainder();
	getThreadRunners_incorrectThreads();
	getThreadRunners_incorrectRemainder();
	getThreadRunners_incorrectHeight();

	// Finish Tests
	return (success == true);
}
