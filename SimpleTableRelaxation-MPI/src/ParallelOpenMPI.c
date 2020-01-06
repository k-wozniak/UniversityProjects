/*
 ============================================================================
 Name        : ParallelOpenMPI.c
 Version     : 1.0
 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mainFunctions.h"
#include "Thread.h"
#include "Computation.h"

#ifdef UNIT_TESTS
#include "Tests.h"
#endif

#define FIRST_ROW 1
#define LAST_ROW 2

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv); // Start MPI

	// Create and populate the structure holding all process information
	ProcessInfo info;
	initialiseEmptyProcessInfo(&info);

	MPI_Comm_rank(MPI_COMM_WORLD, &info.rank); // Process rank
	MPI_Comm_size(MPI_COMM_WORLD, &info.numProcs);

	// Runs unit tests but are excluded in release build
#ifdef UNIT_TESTS
	if(info.rank == 0) { runAllTests(); }
#endif

	// Process input arguments
	int setup = mainSetup(argc, argv, &info);
	if(setup == -1) {
		MPI_Finalize();
		return 0;
	}

	// MPI_Requests required for asynchronous communication
	MPI_Request send[2] = {MPI_REQUEST_NULL, MPI_REQUEST_NULL};
	MPI_Request recieve[3] = {MPI_REQUEST_NULL, MPI_REQUEST_NULL, MPI_REQUEST_NULL};

	// Variables needed for the main loop
	double p, pTemp1, pTemp2;
	int exit;
	bool sendFinished = false;

	// Loop until all processes are finished
	while(1) {
		// Process Averages for the first and last row of the segment
		// So they can be send first and the communication happens while
		// The rest of the rows are computed
		pTemp1 = computeAveragesForRows(info.cols, 1, 1,
				info.readArr, info.writeArr);
		pTemp2 = computeAveragesForRows(info.cols, info.rows-2, info.rows-2,
				info.readArr, info.writeArr);
		p = (pTemp1 > pTemp2) ? pTemp1 : pTemp2;

		// Send the first and the last row to neighbour processes
		// And wait for the processes to get get their computed rows
		// Asynchronous so means the computation can be done while the messages
		// are sent
		if(info.rank > 0) {
			MPI_Wait(&send[0], MPI_STATUS_IGNORE);
			MPI_Isend(info.writeArr[1], info.cols, MPI_DOUBLE, (info.rank-1),
					FIRST_ROW, MPI_COMM_WORLD, &send[0]);
			MPI_Irecv(info.writeArr[0], info.cols, MPI_DOUBLE, (info.rank-1),
					LAST_ROW, MPI_COMM_WORLD, &recieve[2]);
		}
		if(info.rank < (info.numProcs-1)) {
			MPI_Wait(&send[1], MPI_STATUS_IGNORE);
			MPI_Isend(info.writeArr[info.rows-2], info.cols, MPI_DOUBLE,
					(info.rank+1), LAST_ROW, MPI_COMM_WORLD, &send[1]);
			MPI_Irecv(info.writeArr[info.rows-1], info.cols, MPI_DOUBLE,
					(info.rank+1), FIRST_ROW, MPI_COMM_WORLD, &recieve[0]);
		}

		// Compute Average for the rest of the rows
		pTemp1 = computeAveragesForRows(info.cols, 2, info.rows-3,
				info.readArr, info.writeArr);
		p = (pTemp1 > p) ? pTemp1 : p;

		// If precision is reached inform other threads (only once)
		if(p < info.precision && sendFinished == false) {
			// If only one process just return as no need for synch
			if(info.numProcs == 1) { break;	}

			sendFinished = true;
			MPI_Ibarrier(MPI_COMM_WORLD, &recieve[1]);
		}

		// Wait until either barrier is reached by all processes or
		// the first row is delivered to this process
		if(info.rank < (info.numProcs-1)) {
			MPI_Waitany(2, recieve, &exit, MPI_STATUS_IGNORE);
			if(exit == 1) { break; }
		}

		// Wait until either barrier is reached by all processes or
		// the last row is delivered to this process
		if(info.rank > 0) {
			MPI_Waitany(2, &recieve[1], &exit, MPI_STATUS_IGNORE);
			if(exit == 0) { break; }
		}

		swapPointersArrays(&info.readArr, &info.writeArr);
	}

	if(info.print == true) {
		int rows;
		double **arrayToPrint;

		for(int i = 0; i < info.numProcs; i++)
		{
			rows = info.rows - 2;
			arrayToPrint = &info.writeArr[1];

			// If the first segment, display constants
			if(i == 0)
			{
				arrayToPrint = &info.writeArr[0];
				rows++;
			}

			// If the last segment, display constants
			if(i == (info.numProcs-1))
			{
				rows++;
			}

			if(i == info.rank)
			{
				printArray(arrayToPrint, rows, info.cols);
			}

			MPI_Barrier(MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();

	dealocateArray(info.writeArr, info.rows);
	dealocateArray(info.readArr, info.rows);

	return 0;
}