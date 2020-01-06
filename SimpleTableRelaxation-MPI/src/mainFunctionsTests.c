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
	int argc = 7;
	char* argv[] = {"ProgramName", "-testArray", "100", "5", "-p", "0.01", "-print"};

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);
	threadInfo.rank = 0;
	threadInfo.numProcs = 1;

	int out = mainSetup(argc, argv, &threadInfo);

	assert((out != -1), "Something went wrong with input, returned -1");

	assert((threadInfo.cols == 100 && threadInfo.rows == 100),
			"Incorrect row/column number");

	assert((threadInfo.precision == 0.01), "Incorrect precision");

	assert((threadInfo.print == 1), "Print is not enabled.");

	assert((threadInfo.readArr != NULL) && (threadInfo.writeArr != NULL),
			"Read or Write array are null");

	dealocateArray(threadInfo.writeArr, threadInfo.rows);
	dealocateArray(threadInfo.readArr, threadInfo.rows);
}

static void mainSetup_tooSmallArray_ErrorOutput()
{
	int argc = 7;
	char* argv[] = {"ProgramName", "-testArray", "10", "5", "-p", "0.01", "-print"};

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);
	threadInfo.rank = 0;
	threadInfo.numProcs = 10;

	int out = mainSetup(argc, argv, &threadInfo);

	assert((out == -1), "Not corrected output.");
}

static void mainSetup_tooZeroPrecison_ErrorOutput()
{
	int argc = 7;
	char* argv[] = {"ProgramName", "-testArray", "10", "5", "-p", "0", "-print"};


	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);
	threadInfo.rank = 0;
	threadInfo.numProcs = 1;

	int out = mainSetup(argc, argv, &threadInfo);

	assert((out == -1), "Not corrected output.");
}

static void mainSetup_dontPrint_PrintIsFalse()
{
	int argc = 6;
	char* argv[] = { "ProgramName", "-testArray", "12", "5", "-p", "0.01"};

	// Create and populate the structure
	ProcessInfo threadInfo;
	initialiseEmptyProcessInfo(&threadInfo);
	threadInfo.rank = 0;
	threadInfo.numProcs = 1;

	mainSetup(argc, argv, &threadInfo);

	assert(threadInfo.print == false, "Print is not false.");

	dealocateArray(threadInfo.writeArr, threadInfo.rows);
	dealocateArray(threadInfo.readArr, threadInfo.rows);
}

/*
 * coefficients
 */
static void coefficients_correctIn_correctOut()
{
	int p = 5, rows = 22;

	int h1 = getSegmentHeight(0, p, rows);
	int h2 = getSegmentHeight(1, p, rows);
	int h3 = getSegmentHeight(2, p, rows);
	int h4 = getSegmentHeight(3, p, rows);
	int h5 = getSegmentHeight(4, p, rows);

	assert(h1 == 6 || h2 == 6 || h3 == 6 || h4 == 6 || h5 == 6,
			"Incorrect Height.");
}

static void coefficients_moreThreadsThanRows_outZero()
{
	int p = 100, rows = 20;

	int h = getSegmentHeight(0, p, rows);

	assert(h == 0, "Incorrect calculations.");
}

static void coefficients_unevenThreadsToColumnsRetio()
{
	int p = 7, rows = 146;

	int h1 = getSegmentHeight(0, p, rows);
	assert(h1 == 23, "Threads has changed.");

	int h2 = getSegmentHeight(1, p, rows);
	assert(h2 == 23, "Threads has changed.");

	int h3 = getSegmentHeight(2, p, rows);
	assert(h3 == 23, "Threads has changed.");

	int h4 = getSegmentHeight(3, p, rows);
	assert(h4 == 23, "Threads has changed.");

	int h5 = getSegmentHeight(4, p, rows);
	assert(h5 == 22, "Threads has changed.");

	int h6 = getSegmentHeight(5, p, rows);
	assert(h6 == 22, "Threads has changed.");

	int h7 = getSegmentHeight(6, p, rows);
	assert(h7 == 22, "Threads has changed.");
}

bool runAllTests_mainFunctionsTests()
{
	// Test mainSetup
	mainSetup_correctInput_correctOutput();
	mainSetup_tooSmallArray_ErrorOutput();
	mainSetup_tooZeroPrecison_ErrorOutput();
	mainSetup_dontPrint_PrintIsFalse();

	// Test coefficients
	coefficients_correctIn_correctOut();
	coefficients_moreThreadsThanRows_outZero();
	coefficients_unevenThreadsToColumnsRetio();

	// Finish Tests
	return (success == true);
}
