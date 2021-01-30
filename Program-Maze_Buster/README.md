# Maze Buster

It is a program designed for **EE20084 Structured Programming module**. It finds a solution to a maze (if exists) with predefined starting and finishing positions an implementatoin of an A* algorithm.

## Operation
### Input
To ran the program you need to call "MazeBuster -fileLocation -fileDestination [optional]-d

- fileLocation: the location of the file the maze is stored in
- fileDestiantion: the location of the output file with the solution
- -d - is an optional parameter that will print the maze with the soltion in the console

### Input File
Input file has a following structure:

Size_Horizontal Size_Vertical
Start_X Start_Y
End_X End_Y
<The maze with each row separate>

Furthermore, each cell is noted as a sum of walls where **1 - right, 2 - down, 4 - left, 8 - up**.
For example if cell can go down and up it would be marked as 10.

Emaple file:
5 5 (Five rows by five columns)
0 0 (Start at 0,0)
4 4 (Finish at 4,4)
12 10 10 10 9 
6 10 9 13 5 
14 9 6 1 5 
12 2 9 5 5 
7 14 2 3 7

### Output
Output file is created of two rows:
- First, the number of steps required to solve the maze
- Second, path required to take where L(Left), R(Right), U(Up), D(Down) indicate directions taken 