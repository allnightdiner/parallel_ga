#ifndef FILE_COMMON
#define FILE_COMMON

/*
#define GOAL_FIT	(((N-1) * (N-1)) + (N-1))/2	
#define GOAL_FIT	N
#define SUM		((POP_SIZE * POP_SIZE) + POP_SIZE)/2
*/
#define R(x)	(rand()/((RAND_MAX)/x+1))	

/* These make up the individuals of the population. 
 * fitness: the fitness of this particular individual.
 * configuration: is a potential solution to N-queens. 
 */
struct state {
	int fitness;
	int* configuration;
};

/* population configuration struct. 
 * id: used to identify the specific config being used when testing parameters
 * over multiple full runs of the GA.
 * n: the n of n queens. 
 * generation: the specifc generation the population is at during a full run.
 * length_of_run: specifies the maximum generations to allow a run to continue
 * for.
 * sum: The summation of the population size. Used for fitness proportianete 
 * selection. 
 * goal_fit: target fitness for a solution in the population, once achieved a run
 * will stop.
 * cross_rate: the rate of cross over during reproduction of the population.
 * mut_rate: same as above but for mutation. Mutation is done randomly on each
 * index of an individuals configuraiton array.
 * n_of_runs: Specifies the number of runs to use a particular population 
 * configuration for. Used to gather statistics on the efficacy of a particular
 * conf.
 */
struct pop_c {
	int id;
	int pop_size;
	int n;
	int generation;
	int length_of_run;
	int sum;
	int goal_fit;
	//all rates are per 1000
	int cross_rate;
	int mut_rate;
	//int out_count;
	int n_of_runs;
};

/* Struct to hold population fitness statistics */
struct pop_s {
	int* avg_fit;
	int* best_fit;
	int* worst_fit;
	unsigned int** fit_freq;
	int* last_generation;
};

/* test configuration, used to test ranges of specifc values for a particular
 * aspect of the GA like crossover, mutation, etc. The parameter being tested is
 * stored in test_id. 
 */
struct test_c {
	char* test_id;
	int* to_test;
	int start;
	int end;
	int inc;
};

#endif
