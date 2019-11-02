# The Assignment Problem #1

We will approach how we can assign n agents (a) to n tasks (t) such that the total cost (**C**a,t) of assignment is minimized. The matrix of costs is always randomly generated, depending on a seed, thus the minimum cost can change with every execution independently of the n number of agents/tasks.

##  Getting Started
These instructions will help to compile and run developed programs on your local machine.

### Prerequisites
To compile programs, it is necessary to have a C compiler installed on yor local machine, for example cc. 

### Compiling
The following command **compiles assignment program** (*assignment.c*) where <executable_filename>  will be the executable filename: 

```
cc -Wall -O2 assignment.c -o <executable_filename> -lm
```

## Running

**Options:**
```
-e		for n=3 and n=5 using Brute Force strategy
-f <seed>	uses Brute Force strategy with specified Seed value
-b <seed>	uses Branch and Bound strategy with specified Seed value
-r <seed>	uses Brute Force strategy with Random Permutations generated n times and a specified Seed value
	

```



