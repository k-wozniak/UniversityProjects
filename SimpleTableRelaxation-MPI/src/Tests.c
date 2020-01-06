/*
 *  Tests.c
 *
 *  Created on: 11 Nov 2019
 */
#include "Tests.h"

static void runTest(bool output, char errorMessage [], char correctMessage [])
{
	if (output == false)
	{
		printf("\nFinished. %s\n", errorMessage);
	}
	else
	{
		printf("\nFinished. %s\n", correctMessage);
	}
}

void runAllTests()
{
	runTest(
		runAllTests_computationTests(),
		"Computation Tests FAILED!!! -------- -------- --------",
		"Computation Tests Success."
	);

	runTest(
		runAllTests_threadTests(),
		"Thread Tests FAILED!!! -------- -------- --------",
		"Thread Tests Success."
	);

	runTest(
		runAllTests_mainFunctionsTests(),
		"Main Tests FAILED!!! -------- -------- --------",
		"Main Tests Success."
	);
}