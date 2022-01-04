# CM30225 Parallel Computing Assessed Coursework Assignment 1

## Specification

The objective of this assignment is to give you experience of using a cluster; using pthread parallelism on a sharedmemory architecture; plus a feel for how parallel problems scale on such architectures.

The background is the solution of differential equations using a method called therelaxation technique. This is done byhaving an array of values and repeatedly replacing a value with the average of its four neighbours; excepting boundaryvalues, which remain at fixed values. This is repeated until all values settle down to within a given precision.

This assignment is to implement relaxation, using C and pthreads on Balena.

**For this assignment you will be simply repeatedly averaging sets of four numbers.**

Your solver will expect an initial square array ofdoublevalues, an integer dimension (the dimension of the array),the number of threads to use, and a precision to work to (e.g., 0.01 or 0.0001 or whatever).

The edges of the array form the boundary, values there are fixed; iterate the averaging until the new values of allelements differ from the previous ones by less than the precision.

## Feedback

Grade 60/100

The main disadvange of the program was it limited investigation due to my wrong design to input entire array thorught the command line. (Limiting the array size). I had no time to correct it. The git version includes functionality to read the array from the file. I recomend making a new input variable like "-TestArray Size Border" and create array just for testing.

Additionally, my report was not the best and I should of spend some more time on it.
