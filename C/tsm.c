#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

// globals
int **cityMatrix;
int N;

//used in branch_and_bound
int *visited;
int* bestCase;
int smallest_path = 10000;
int rounds = 0;

//used in greedy
int greedy_sum = 0;

//used in genetic algorithm
int **population;
int fitest_index;
int best_fitness = 100000;
int* thread_count;
int* fitness_chart;

void get_input(char filename[])
{
	FILE * fp;
	int i,j;  
	fp = fopen(filename, "r");
	if(!fp)
	{
		printf("Cannot open file %s\n", filename);
		exit(1);
	}

	cityMatrix = (int**)malloc(N* sizeof(int*));		
	for(i = 0; i < N; i++)
	{
		cityMatrix[i] = (int*)malloc(N * sizeof(int*));
	}

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			fscanf(fp,"%d ", &cityMatrix[i][j]); 

		}

	}
  fclose(fp); 
}

//evlauate the fitness of a single path
int fitness_eval(int index)
{
	int i;
	int fitness = 0;
	for(i = 0; i < N-1; i++)
	{
		fitness += cityMatrix[population[index][i]][population[index][i+1]];
	}
	 return fitness;
}

//find fitest member of sub population
int sub_find_fittest(int start, int stop)
{
	int i; 
	int best_sum = 10000;
	int index;
	//should have good cache performance, fitness_chart is stored sequentially since its an array
	for(i = start; i < stop; i++)
	{
		if(fitness_chart[i] < best_sum)
		{
			best_sum = fitness_chart[i];
			index = i;
		}
	}
	return index;
}

//finds the best fitness and stores it globally by index
void find_fittest(int population_size, int iteration_index)
{
	int sub_population = population_size/(*thread_count);
	int leftover = population_size % (*thread_count);
	
	#pragma omp parallel num_threads(*thread_count) 
	{
		int thread = omp_get_thread_num();
		
		int start, stop;
		if(thread < leftover)
		{
			start = thread * sub_population;
			stop = start + sub_population + 1; 
		} else
		{
			start = thread * sub_population + leftover;
			stop = start + sub_population;
		}
		int local_best_index = sub_find_fittest(start, stop);
		#pragma omp critical
		{
			if (fitness_chart[local_best_index] < best_fitness)
			{
				best_fitness = fitness_chart[local_best_index];
				fitest_index = local_best_index;
			}
		}
	}
}

//finds the worst path from the subset of the population
int worst_fitness(int population_size, int micro_population_size)
{
	int i;
	int local_worst = 0;
	int local_worst_index;
	for(i = 0; i < micro_population_size; i++)
	{
		int population_index = rand() % population_size;
		if (fitness_chart[population_index] > local_worst)
		{
			local_worst = fitness_chart[population_index];
			local_worst_index = population_index;
		}
	}
	return local_worst_index;
}

//mutates a path, mutates 1 path with a swap based on mutation rate
void mutate_paths(int population_size, int mutation_rate)
{
	int i; 
	//#pragma omp parallel for num_threads(*thread_count)
	for(i = 0; i < population_size; i++)
	{
		if(i != fitest_index)
		{
			int j;
			for(j = 1; j < N; j++)
			{
				if( (rand() % 100) <= mutation_rate )
				{
					int position_random = 1 + (rand() % (N-1));
					if(j != position_random)
					{
						
						int temp = population[i][position_random];
						population[i][position_random] = population[i][j];
						population[i][j] = temp;
					}
				}	
			}
		}
		//evaluate fitness at this time also and update the list
		fitness_chart[i] = fitness_eval(i);
	}
}

//selects a best from a subset of the population chosen randomly
int reproduction_selection(int population_size, int micro_population_size)
{
	int i;
	int local_fittest = 10000;
	int local_fittest_index;
	for(i = 0; i < micro_population_size; i++)
	{
		int population_index = rand() % population_size;
		if (fitness_chart[population_index] < local_fittest)
		{
			local_fittest = fitness_chart[population_index];
			local_fittest_index = population_index;
		}
	}
	return local_fittest_index;
}

//reporduces two paths 
void reproduction(int population_size, int parent_index_one, int parent_index_two, int micro_population_size)
{
	int i, j;
	int start = 3;
	int stop = 6;
	int arr[N];
	//creates an array, didn't wanna do it in place
	for(i = 0; i < N; i++)
	{
		arr[i] = 0;
	}
	//slices the start and stop from the 1st parent
	for(i = 1; i < N; i++)
	{
		if(start < stop && i >= start && i < stop)
		{
			arr[i] = population[parent_index_one][i];
		}
	}
	int current_next_index = 1;
	//fills in the rest witht he seccond parent
	for(i = 1; i < N; i++)
	{
		int nextIndex = population[parent_index_two][i];
		int isPresent = 0;
		for(j = start; j <= stop; j++)
		{
			if(arr[j] == nextIndex)
			{
				isPresent = 1;
				break;
			}
		}
		if (isPresent == 0)
		{
			for(j = current_next_index; j < N; j++)
			{
				if (start < stop && (j < start || j >= stop)) 
				{
					arr[j] = nextIndex;
					current_next_index = j+1;
					break;
				}
			}
		}
	}

	//gets a local worst case, replaces it with the child
	int worst_index = worst_fitness(population_size, micro_population_size);
	for(i = 1; i < N; i++)
	{
		population[worst_index][i] = arr[i];
	}

}

//evolves the poplation
//selects two parents from a micro_population, then reproduces them
int evolve(int population_size, int micro_population_size)
{
	int parent_index_one, parent_index_two, i, worst_place_index;
	for(i = 0; i < population_size; i++)
	{
		if(i != fitest_index)
		{
			parent_index_one = reproduction_selection(population_size, micro_population_size);
			parent_index_two = reproduction_selection(population_size, micro_population_size);
			reproduction(population_size, parent_index_one, parent_index_two, micro_population_size);
		}
	}
}


//suffle and initialize array
void init_random_path(int index)
{
	int i, j;
	population[index][0] = 0;
	for(i = 1; i < N; i++)
	{
		//start off with the simplist, but not most uniform method
		//random number btwn 0. i;
		j = (rand() % (i)) + 1;
		if(j!=i)
		{
			population[index][i] = population[index][j];
		}
		population[index][j] = i;
	}
}

//generates path, sets fitness of the path
void generate_path(int index, int* fitness)
{
	init_random_path(index);
	*fitness = fitness_eval(index);
}


//debugging tool, prints population at this time
void print_population(int population_size)
{
	int i, j;
	for(i = 0; i < population_size; i++)
	{
		printf("\n fitness: %d \t:", fitness_chart[i]);
		for(j = 0; j < N; j++)
		{
			printf("%d -> " , population[i][j]);
		}
	}
}

//genetic algorithm. 
//runs in something like O(population_size * N * iterations) 
//much faster than N!, depending on how its set up, iterations is the largest number present
//it can get a pretty good solution very quickly
//fitness chart is a list of all the tour sizes, such that population[index][0...N]'s fitness is stored in fitnesChart[index]
void init_population(int population_size, int iterations, int mutation_rate)
{
	int i;
	int micro_population_size = 25;
	//generate population_size paths.


	#pragma omp parallel for num_threads(*thread_count)
	for(i = 0; i < population_size; i++)
	{
		generate_path(i, &fitness_chart[i]);
	}
	//print_population(population_size);

	//select the fitest
	find_fittest(population_size, 0);
	//print_population(population_size, fitness_chart);

	//loop iterations times, evolve, mutate, and find the fitest
	for(i = 1; i < iterations; i++)
	{
		evolve(population_size, micro_population_size);
		mutate_paths(population_size, mutation_rate);
		find_fittest(population_size, i);
	//	print_population(population_size);
	}

	//print_population(population_size);
}


//2nd naive attempt
//compares most solutions
//not feasable after N is above 14
//but it gives an exact solution
void branch_and_bound(int n, int* thisSolution, int* unVisited, int sum)
{
	int i;
	if(n == 1)
	{

		thisSolution[N-1] = unVisited[0];
		if(sum+cityMatrix[thisSolution[N-2]][unVisited[0]] < smallest_path)
		{
			smallest_path = sum+cityMatrix[thisSolution[N-2]][unVisited[0]];
			for(i = 0; i < N; i++)
		{
			bestCase[i] = thisSolution[i];
		}
		}
	}
	else
	{
		for(i = 0; i < n; i++)
		{
			thisSolution[N-n] = unVisited[i];
			int temp = unVisited[i];
			unVisited[i] = unVisited[n-1];			
			if(sum+cityMatrix[thisSolution[N-(n+1)]][temp] < smallest_path)
			{
				rounds++;
				branch_and_bound(n-1, thisSolution, unVisited, sum+cityMatrix[thisSolution[N-(n+1)]][temp]);
			}
			int temp2 = unVisited[i];
			unVisited[i] = temp;
			unVisited[n-1] = temp2;
		}
	}
}

//greedy algorithm
//first naive attempt. 
//kept as a comparison
void greedy()
{
	int i, j;
	int* visited = (int*)malloc(N*sizeof(int));
	for(i = 0; i < N; i++)
	{
		visited[i] = 0;
	}
	visited[0] = 1;

	int smallest;
	int tracker = 0;
	int nextTracker = -1;
	int sum = 0;

	for(i = 0; i < N; i++)
	{
		smallest= 100000;
		for(j = 0; j < N; j++)
		{
			if(cityMatrix[tracker][j] < smallest && tracker != j && visited[j] != 1)
			{
				smallest = cityMatrix[tracker][j];
				nextTracker = i;
			}
		}
		visited[nextTracker] = 1;
		sum += cityMatrix[tracker][nextTracker];
		//bestCase[i] = tracker;
		tracker = nextTracker;
	}
	greedy_sum = sum;

	printf("greedy: %d", greedy_sum);

}


int main(int argc, char *argv[])
{
	//initialize the algorithms
	if(argc != 3)
	{
		printf("Usage: ./tsm citiesXXX.txt number_of_threads \n");
		exit(0);
	}
	bestCase = (int*)malloc(N * sizeof(int));
	int i;
	char* input_file = argv[1];
	int j = 0;
	char number[3]; //max city length 3 digits

	for(i = 0; i <12; i++)
	{
		if(input_file[i] >= '0' && input_file[i] <= '9')
		{
			number[j++]= input_file[i];
		} else if (input_file[i] == '.')
		{
			break;
		}
	}
	N = atoi(number);
	get_input(argv[1]);
	thread_count = malloc(sizeof(int*));
	*thread_count = atoi(argv[2]);
	



	omp_set_num_threads(*thread_count);


	//set rates for everything
	int population_size = 1000;
	fitness_chart = malloc(population_size * sizeof(int));
	int iterations = 1000;
	int mutation_rate = 2; //percent
	population = (int**)malloc(population_size* sizeof(int*));		
	for(i = 0; i < population_size; i++)
	{
		population[i] = (int*)malloc(N * sizeof(int*));
	}

	//seeds generator with time
	srand(time(NULL));
	init_population(population_size, iterations, mutation_rate);
	free(fitness_chart);
	//prints the best path

	printf("\n best fitness =  %d \n", best_fitness);

	for(i = 0; i < N; i++)
	{
		printf("%d->", population[fitest_index][i]);
	}
	printf("\n");


	exit(0);
	
}
