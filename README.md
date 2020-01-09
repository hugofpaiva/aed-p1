
# The Assignment Problem #1

We will approach how we can assign n agents (a) to n tasks (t) such that the total cost (**C**a,t) of assignment is minimized. The matrix of costs is always randomly generated, depending on a seed, thus the minimum cost can change with every execution independently of the n number of agents/tasks.

##  Getting Started
These instructions will help to compile and run developed programs on your local machine.

### Prerequisites
To compile programs, it is necessary to have a C compiler installed on your local machine, for example cc. 

### Compiling
The following command **compiles assignment program** (*assignment.c*) where <executable_filename>  will be the executable filename: 

```
cc -Wall -O2 assignment.c -o <executable_filename> -lm
```

## Running

**Options:**
```
-e				  		for n=3 and n=5 using Brute Force method
-f <seed>					uses Brute Force method with specified Seed value
-b <seed>					uses Branch and Bound method with specified Seed value
-r <seed> <seed> <seed> <N>	                uses Brute Force method with Random Permutations generated N times and three specified Seed value
-g <seed> 					uses Greedy method with specified Seed value
-a <seed>                                       runs all the previous methods with specified Seed value and Random Permutations 1000000 times
```
## Details
All the details, including the results, can be found in the [Work Report](/relatorio/AED_Report.pdf).

## Authors

 - **Hugo Paiva de Almeida - 93195**
 - **João Laranjo - 91153**
 - **Lucas Sousa - 93019**
 
  ## Nota
Classificação obtida de **19** valores em 20.

