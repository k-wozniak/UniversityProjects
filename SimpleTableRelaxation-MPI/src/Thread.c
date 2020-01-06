/*
 * Thread.c
 *
 *  Created on: 11 Nov 2019
 */

#include "Thread.h"

void initialiseEmptyProcessInfo(ProcessInfo* info)
{
	info->readArr = NULL;
	info->writeArr = NULL;

	info->cols = 0;
	info->rows = 0;
	info->precision = 0.1;

	info->numProcs = -1;
	info->rank = -1;

	info->print = false;
}
