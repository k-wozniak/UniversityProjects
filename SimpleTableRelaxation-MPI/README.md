# CM30225 Parallel ComputingAssessed Coursework Assignment 2

## Specification

The objective of this assignment is to give you experience of using MPI on a distributed memory architecture; plus afeel for how parallel problems scale on such architectures.

The problem to solve is the same as Assignment 1. But, now, you will be using MPI on a distributed memoryarchitecture.

As before, run your code on varying sizes of arrays and varying numbers of cores, but in a distributed memoryconfiguration.

A complete solution consists of

* properly commented source code, together with any extra information you feel will help, such as describingyour approach to the parallelisation of your solution, how you thought about messaging overhead, and so on

* (excerpts from) the results of yourcorrectness testingof your code with a description of your testing process

* comments, graphs or any other relevant details of yourscalability investigation, with particular reference tospeedup and efficiency

Contains software project created during the my university program.

## Feedback

Grade 83/100

* A bit over-engineered? - I fallowed TTD and implemented extensive input functionality. So probably, but at the same time hopefully a high quality code

* Generally good code (though you do need better commenting to explain your
strategies) For example a comment:
"// Asynchronous so means the computation can be done while the messages (...)"

Did you find this was better than the simpler Sendrevc?  You need careful commenting in your code to explain how you avoid races on the buffers MPI_Ibarrier() why a barrier? More explanation needed(barriers are not normally needed in MPI) - it was also noted as part of the feedback that it is explained well in the report. Therefore, requires more clear explanatin in the code.

* Scalability investigation.
Note that 1500 is still quite small for MPI. Larger matrices are needed to see the true benefit of MPI. I capped the maximum size of the array to the maximum size possible to compute in the time limit on a single core. Therefore, I suggest to remove this limitation and compute maximum times for each configuration.