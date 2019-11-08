////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AED, 2019/2020
//
//   93195 Hugo Filipe Ribeiro Paiva de Almeida
//  93019 José Lucas Sousa
//  91153 João Laranjo
//
// Brute-force solution of the assignment problem (https://en.wikipedia.org/wiki/Assignment_problem)
//
// Compile with "cc -Wall -O2 assignment.c -lm" or equivalent
//
// In the assignment problem we will solve here we have n agents and n tasks; assigning agent
//   a
// to task
//   t
// costs
//   cost[a][t]
// The goal of the problem is to assign one agent to each task such that the total cost is minimized
// The total cost is the sum of the costs
//
// Things to do:
//   0. (mandatory)
//      Place the student numbers and names at the top of this file
//   1. (highly recommended)
//      Read and understand this code
//   2. (mandatory)
//      Modify the function generate_all_permutations to solve the assignment problem
//      Compute the best and worst solutions for all problems with sizes n=2,...,14 and for each
//      student number of the group
//   3. (mandatory)
//      Calculate and display an histogram of the number of occurrences of each cost
//      Does it follow approximately a normal distribution?
//      Note that the maximum possible cost is n * t_range
//   4. (optional)
//      For each problem size, and each student number of the group, generate one million (or more!)
//      random permutations and compute the best and worst solutions found in this way; compare
//      these solutions with the ones found in item 2
//      Compare the histogram computed in item 3 with the histogram computed using the random
//      permutations
//   5. (optional)
//      Try to improve the execution time of the program (use the branch-and-bound technique)
//   6. (optional)
//      Surprise us, by doing something more!
//   7. (mandatory)
//      Write a report explaining what you did and presenting your results
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define NDEBUG  // uncomment to skip disable asserts (makes the code slightly faster)
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// problem data
//
// max_n ........ maximum problem size
// cost[a][t] ... cost of assigning agent a to task t
//

//
// if your compiler complains about srandom() and random(), replace #if 0 by #if 1
//
#if 0
#define srandom srand
#define random rand
#endif

#define max_n 32            // do not change this (maximum number of agents, and tasks)
#define range 20            // do not change this (for the pseudo-random generation of costs)
#define t_range (3 * range) // do not change this (maximum cost of an assignment)

static int cost[max_n][max_n];
static int seed; // place a student number here!
static int min_init_cost;
static int max_init_cost;

static void init_costs(int n)
{
  if (n == -3)
  { // special case (example for n=3)
    cost[0][0] = 3;
    cost[0][1] = 8;
    cost[0][2] = 6;
    cost[1][0] = 4;
    cost[1][1] = 7;
    cost[1][2] = 5;
    cost[2][0] = 5;
    cost[2][1] = 7;
    cost[2][2] = 5;
    return;
  }
  if (n == -5)
  { // special case (example for n=5)
    cost[0][0] = 27;
    cost[0][1] = 27;
    cost[0][2] = 25;
    cost[0][3] = 41;
    cost[0][4] = 24;
    cost[1][0] = 28;
    cost[1][1] = 26;
    cost[1][2] = 47;
    cost[1][3] = 38;
    cost[1][4] = 21;
    cost[2][0] = 22;
    cost[2][1] = 48;
    cost[2][2] = 26;
    cost[2][3] = 14;
    cost[2][4] = 24;
    cost[3][0] = 32;
    cost[3][1] = 31;
    cost[3][2] = 9;
    cost[3][3] = 41;
    cost[3][4] = 36;
    cost[4][0] = 24;
    cost[4][1] = 34;
    cost[4][2] = 30;
    cost[4][3] = 35;
    cost[4][4] = 45;
    return;
  }
  assert(n >= 1 && n <= max_n);
  srandom((unsigned int)seed * (unsigned int)max_n + (unsigned int)n);
  min_init_cost = cost[0][0];
  max_init_cost = cost[0][0];
  for (int a = 0; a < n; a++)
    for (int t = 0; t < n; t++)
    {
      cost[a][t] = 3 + (random() % range) + (random() % range) + (random() % range); // [3,3*range]
      if (cost[a][t] < min_init_cost)
        min_init_cost = cost[a][t];
      if (cost[a][t] > max_init_cost)
        max_init_cost = cost[a][t];
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// code to measure the elapsed time used by a program fragment (an almost copy of elapsed_time.h)
//
// use as follows:
//
//   (void)elapsed_time();
//   // put your code to be time measured here
//   dt = elapsed_time();
//   // put morecode to be time measured here
//   dt = elapsed_time();
//
// elapsed_time() measures the CPU time between consecutive calls
//

#if defined(__linux__) || defined(__APPLE__)

//
// GNU/Linux and MacOS code to measure elapsed time
//

#include <time.h>

static double elapsed_time(void)
{
  static struct timespec last_time, current_time;

  last_time = current_time;
  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &current_time) != 0)
    return -1.0; // clock_gettime() failed!!!
  return ((double)current_time.tv_sec - (double)last_time.tv_sec) + 1.0e-9 * ((double)current_time.tv_nsec - (double)last_time.tv_nsec);
}

#endif

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)

//
// Microsoft Windows code to measure elapsed time
//

#include <windows.h>

static double elapsed_time(void)
{
  static LARGE_INTEGER frequency, last_time, current_time;
  static int first_time = 1;

  if (first_time != 0)
  {
    QueryPerformanceFrequency(&frequency);
    first_time = 0;
  }
  last_time = current_time;
  QueryPerformanceCounter(&current_time);
  return (double)(current_time.QuadPart - last_time.QuadPart) / (double)frequency.QuadPart;
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// place to store best and worst solutions (also code to print them)
//

static int min_cost, min_cost_assignment[max_n]; // smallest cost information
static int max_cost, max_cost_assignment[max_n]; // largest cost information
static long n_visited;                           // number of permutations visited (examined)
// place your histogram global variable here
static int histogram[max_n * t_range]; // Cada valor do array histogram corresponde ao numero de ocorrências do custo, que é o indice desse valor
static double cpu_time;

#define minus_inf -1000000000 // a very small integer
#define plus_inf +1000000000  // a very large integer

static void reset_solutions(void)
{
  min_cost = plus_inf;
  max_cost = minus_inf;
  n_visited = 0l;
  // place your histogram initialization code here
  memset(histogram, 0, sizeof(histogram));
  cpu_time = 0.0;
}

#define show_info_1 (1 << 0)
#define show_info_2 (1 << 1)
#define show_costs (1 << 2)
#define show_min_solution (1 << 3)
#define show_max_solution (1 << 4)
#define show_histogram (1 << 5)
#define show_all (0xFFFF)

static void show_solutions(int n, char *header, int what_to_show)
{
  printf("%s\n", header);
  if ((what_to_show & show_info_1) != 0)
  {
    printf("  seed .......... %d\n", seed);
    printf("  n ............. %d\n", n);
  }
  if ((what_to_show & show_info_2) != 0)
  {
    printf("  visited ....... %ld\n", n_visited);
    printf("  cpu time ...... %.3fs\n", cpu_time);
  }
  if ((what_to_show & show_costs) != 0)
  {
    printf("  costs .........");
    for (int a = 0; a < n; a++)
    {
      for (int t = 0; t < n; t++)
        printf(" %2d", cost[a][t]);
      printf("\n%s", (a < n - 1) ? "                 " : "");
    }
  }
  if ((what_to_show & show_min_solution) != 0)
  {
    printf("  min cost ...... %d\n", min_cost);
    if (min_cost != plus_inf)
    {
      printf("  assignement ...");
      for (int i = 0; i < n; i++)
        printf(" %d", min_cost_assignment[i]);
      printf("\n");
    }
  }
  if ((what_to_show & show_max_solution) != 0)
  {
    printf("  max cost ...... %d\n", max_cost);
    if (max_cost != minus_inf)
    {
      printf("  assignement ...");
      for (int i = 0; i < n; i++)
        printf(" %d", max_cost_assignment[i]);
      printf("\n");
    }
  }
  if ((what_to_show & show_histogram) != 0)
  {
    // place your code to print the histogram here
    FILE *f = fopen("ocorrencias.txt", "w");
    FILE *gnu = fopen("ocorrenciasgnu.txt", "w");
    if (f == NULL)
    {
      printf("Erro a abrir o ficheiro ocorrencias!\n");
      exit(1);
    }
    if (gnu == NULL)
    {
      printf("Erro a abrir o ficheiro ocorrenciasgnu!\n");
      exit(1);
    }

    for (int i = 0; i < max_n * t_range; i++)
    {
      fprintf(f, "%d\n", histogram[i]);
      fprintf(gnu, "%d\t%d\n", i, histogram[i]);
    }
    fclose(f);
    fclose(gnu);

    //int status = system("gnuplot -e \" plot 'ocorrenciasgnu.txt'  title 'Values by Color'\");
    //int codigou = system("gnuplot -e \"set terminal jpeg; plot 'ocorrenciasgnu.txt' with linespoints linestyle 1\" > out.jpg"); // para sair uma imagem pelo gnu plot. Tem de ser retificado.
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// code used to generate all permutations of n objects
//
// n ........ number of objects
// m ........ index where changes occur (a[0], ..., a[m-1] will not be changed)
// a[idx] ... the number of the object placed in position idx
//
// TODO: modify the following function to solve the assignment problem
//

void printAssignment(int n, int a[n])
{
  printf("  assignment ...");
  for (int i = 0; i < n; i++)
    printf(" %d", a[i]);
  printf("\n");
}

int costAssignment(int n, int a[n])
{
  int permutation_cost = 0;

  for (int i = 0; i < n; i++)
  {
    permutation_cost += cost[i][a[i]];
  }
  histogram[permutation_cost]++;
  //printf("Custo: %d \n",custo);
  return permutation_cost;
}

static void generate_all_permutations(int n, int m, int a[n]) // é introduzido um vetor a que vai de 0 até n
{
  if (m < n - 1)
  {
    //
    // not yet at the end; try all possibilities for a[m]
    //
    for (int i = m; i < n; i++)
    {
#define swap(i, j) \
  do               \
  {                \
    int t = a[i];  \
    a[i] = a[j];   \
    a[j] = t;      \
  } while (0)
      swap(i, m);                             // exchange a[i] with a[m]
      generate_all_permutations(n, m + 1, a); // recurse
      swap(i, m);                             // undo the exchange of a[i] with a[m]
#undef swap
    }
  }
  else // devido à recursividade, chega a uma altura que o m passa a ser igual ao n e portanto faz este else. Desta forma, vai correr todos os "a"s.
  {
    //
    // visit the permutation (TODO: change this ...)
    //
    //printAssignment(n,a); //Apenas para debugging para conseguir perceber melhor o problema.

    int permutation_cost = costAssignment(n, a); //Custo total

    if (permutation_cost > max_cost)
    {
      max_cost = permutation_cost;
      for (int i = 0; i < n; i++)
        max_cost_assignment[i] = a[i];
    }

    if (permutation_cost < min_cost)
    {
      min_cost = permutation_cost;
      for (int i = 0; i < n; i++)
        min_cost_assignment[i] = a[i];
    }

    n_visited++;
    // place your code to update the best and worst solutions, and to update the histogram here
  }
}

static void generate_all_permutations_branch_and_bound(int n, int m, int a[n], int partial_cost) // é introduzido um vetor a que vai de 0 até n
{
  if (min_cost < (min_init_cost * (n - m) + partial_cost))
    return;
  else
  {
    if (m < n - 1)
    {
      //
      // not yet at the end; try all possibilities for a[m]
      //
      for (int i = m; i < n; i++)
      {
#define swap(i, j) \
  do               \
  {                \
    int t = a[i];  \
    a[i] = a[j];   \
    a[j] = t;      \
  } while (0)
        swap(i, m);                                                                              // exchange a[i] with a[m]
        generate_all_permutations_branch_and_bound(n, m + 1, a, (partial_cost + cost[m][a[m]])); // recurse
        swap(i, m);                                                                              // undo the exchange of a[i] with a[m]
#undef swap
      }
    }
    else // devido à recursividade, chega a uma altura que o m passa a ser igual ao n e portanto faz este else. Desta forma, vai correr todos os "a"s.
    {
      //
      // visit the permutation (TODO: change this ...)
      //
      //printAssignment(n,a); //Apenas para debugging para conseguir perceber melhor o problema.

      int permutation_cost = costAssignment(n, a); //Custo total

      // Meter isto tudo simplificado numa função em que entre o custo e o a, p. ex definecost(custo,a)

      if (permutation_cost < min_cost)
      {
        min_cost = permutation_cost;
        for (int i = 0; i < n; i++)
          min_cost_assignment[i] = a[i];
      }

      n_visited++;
      // place your code to update the best and worst solutions, and to update the histogram here
    }
  }
}

static void generate_all_permutations_branch_and_bound_max(int n, int m, int a[n], int partial_cost) // é introduzido um vetor a que vai de 0 até n
{
  if (max_cost > (max_init_cost * (n - m) + partial_cost))
    return;
  else
  {
    if (m < n - 1)
    {
      //
      // not yet at the end; try all possibilities for a[m]
      //
      for (int i = m; i < n; i++)
      {
#define swap(i, j) \
  do               \
  {                \
    int t = a[i];  \
    a[i] = a[j];   \
    a[j] = t;      \
  } while (0)
        swap(i, m);                                                                                  // exchange a[i] with a[m]
        generate_all_permutations_branch_and_bound_max(n, m + 1, a, (partial_cost + cost[m][a[m]])); // recurse
        swap(i, m);                                                                                  // undo the exchange of a[i] with a[m]
#undef swap
      }
    }
    else // devido à recursividade, chega a uma altura que o m passa a ser igual ao n e portanto faz este else. Desta forma, vai correr todos os "a"s.
    {
      //
      // visit the permutation (TODO: change this ...)
      //
      //printAssignment(n,a); //Apenas para debugging para conseguir perceber melhor o problema.

      int permutation_cost = costAssignment(n, a); //Custo total

      // Meter isto tudo simplificado numa função em que entre o custo e o a, p. ex definecost(custo,a)
      if (permutation_cost > max_cost)
      {
        max_cost = permutation_cost;
        for (int i = 0; i < n; i++)
          max_cost_assignment[i] = a[i];
      }

      n_visited++;
      // place your code to update the best and worst solutions, and to update the histogram here
    }
  }
}
static void greedy_method(int n, int a[n])
{
  int binary_array_vertical[n];
  for (int i = 0; i < n; i++)
  {
    binary_array_vertical[i] = 0;
  }

  int l, c = n;
  int element_cost = 0;
  int first_element_cost, second_element_cost = 0;
  for (int i = 0; i < l; i++)
  {
    printf("%d -------- \n", cost[l][0]);
    for (int i = 0; i < c - 1; i++)
    {
      first_element_cost = cost[l][c];
      second_element_cost = cost[l][c + 1];
      if (first_element_cost < second_element_cost)
      {
        min_cost = first_element_cost;
      }
      else
      {
        min_cost = second_element_cost;
      }
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
// function to generate a pseudo-random permutation
//

void random_permutation(int n, int t[n])
{
  assert(n >= 1 && n <= 1000000);
  for (int i = 0; i < n; i++)
    t[i] = i;
  for (int i = n - 1; i > 0; i--)
  {
    int j = (int)floor((double)(i + 1) * (double)random() / (1.0 + (double)RAND_MAX)); // range 0..i
    assert(j >= 0 && j <= i);
    int k = t[i];
    t[i] = t[j];
    t[j] = k;
  }

  int permutation_cost = costAssignment(n, t); //Custo total

  if (permutation_cost > max_cost)
  {
    max_cost = permutation_cost;
    for (int i = 0; i < n; i++)
    {
      max_cost_assignment[i] = t[i];
    }
  }

  if (permutation_cost < min_cost)
  {
    min_cost = permutation_cost;
    for (int i = 0; i < n; i++)
      min_cost_assignment[i] = t[i];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// main program
//

int main(int argc, char **argv)
{
  if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'e')
  {
    seed = 0;
    {
      int n = 3;
      init_costs(-3); // costs for the example with n = 3
      int a[n];
      for (int i = 0; i < n; i++)
        a[i] = i;

      reset_solutions();
      (void)elapsed_time();
      generate_all_permutations(n, 0, a);
      printf("metodo greedy ----------\n");
      greedy_method(n, a);
      cpu_time = elapsed_time();
      show_solutions(n, "Example for n=3", show_all);
      printf("\n");
    }
    {
      int n = 5;
      init_costs(-5); // costs for the example with n = 5
      int a[n];
      for (int i = 0; i < n; i++)
        a[i] = i;
      reset_solutions();
      (void)elapsed_time();
      generate_all_permutations(n, 0, a);
      cpu_time = elapsed_time();
      show_solutions(n, "Example for n=5", show_all);
      return 0;
    }
  }
  if (argc == 3)
  {
    if (argv[1][0] == '-' && argv[1][1] == 'f')
    {
      seed = atoi(argv[2]); // seed = student number
      if (seed >= 0 && seed <= 1000000)
      {
        for (int n = 1; n <= max_n; n++)
        {
          init_costs(n);
          show_solutions(n, "Problem statement", show_info_1 | show_costs);
          //
          // 2.
          //
          if (n <= 14) // use a smaller limit here while developing your code
          {
            int a[n];
            for (int i = 0; i < n; i++)
              a[i] = i; // initial permutation
            reset_solutions();
            (void)elapsed_time();
            generate_all_permutations(n, 0, a);
            cpu_time = elapsed_time();
            show_solutions(n, "Brute force", show_info_2 | show_min_solution | show_max_solution);
          }
        }
      }
      printf("\n");
      return 0;
    }

    if (argv[1][0] == '-' && argv[1][1] == 'b')
    {
      seed = atoi(argv[2]); // seed = student number
      if (seed >= 0 && seed <= 1000000)
      {
        for (int n = 1; n <= max_n; n++)
        {
          init_costs(n);

          //
          // place here your code that solves the problem with branch-and-bound
          //

          if (n <= 16) // use a smaller limit here while developing your code
          {

            int a[n];
            for (int i = 0; i < n; i++)
              a[i] = i; // initial permutation
            reset_solutions();
            (void)elapsed_time();
            generate_all_permutations_branch_and_bound(n, 0, a, 0);
            generate_all_permutations_branch_and_bound_max(n, 0, a, 0);
            cpu_time = elapsed_time();
            printf("%d\n", n);
            show_solutions(n, "Brute force with branch-and-bound", show_info_2 | show_min_solution | show_max_solution);
          }
        }
      }
      printf("\n");
      return 0;
    }
  }
  if (argc == 6)
  {
    if (argv[1][0] == '-' && argv[1][1] == 'r')
    {
      int N = atoi(argv[5]);
      int iterations = 0;
      for (int i = 2; i <= 4; i++)
      {
        seed = atoi(argv[i]); // seed = student number
        if (seed >= 0 && seed <= 1000000)
        {
          for (int n = 13; n <= 14; n++)
          {
            init_costs(n);
            show_solutions(n, "Problem statement", show_info_1 | show_costs);
            reset_solutions();
            (void)elapsed_time();
            //pow(10,6)
            for (int z = 1; z <= N; z++)
            {
              iterations++;
              int a[n];
              for (int l = 0; l < n; l++)
                a[l] = l; // initial permutation
              random_permutation(n, a);
            }
            cpu_time = elapsed_time();
            show_solutions(n, "Random Permutation", show_info_1 | show_min_solution | show_max_solution);
          }
        }
      }
      printf("\n");
      return 0;
    }
  }

  fprintf(stderr, "usage: %s -e              # for the examples\n", argv[0]);
  fprintf(stderr, "usage: %s student_number\n", argv[0]);
  return 1;
}
