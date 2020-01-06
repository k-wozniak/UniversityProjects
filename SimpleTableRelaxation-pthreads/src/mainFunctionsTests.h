/*
 * mainFunctionsTests.h
 *
 *  Created on: 11 Nov 2019
 */

#ifndef MAINFUNCTIONSTESTS_H_
#define MAINFUNCTIONSTESTS_H_

#include <pthread.h>
#include <stdbool.h>
#include "Thread.h"
#include "mainFunctions.h"

/**
 * Run all the unit tests for mainFunctions
 * returns true if all succeeded false if any failed
 */
bool runAllTests_mainFunctionsTests();

#endif /* MAINFUNCTIONSTESTS_H_ */
