#ifndef FILE_COMMON
#define FILE_COMMON

/*
#define GOAL_FIT	(((N-1) * (N-1)) + (N-1))/2	
#define GOAL_FIT	N
#define SUM		((POP_SIZE * POP_SIZE) + POP_SIZE)/2
*/
#define R(x)	(rand()/((RAND_MAX)/x+1))	


struct state {
	int fitness;
	//static allocation?
	int* configuration;
};

/* population configuration struct. */
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
	int inversion_rate;
	char pop_file_id[20];
	int out_count;
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
 * aspect of the GA like crossover, mutation, etc
 */
struct test_c {
	char* test_id;
	int* to_test;
	int start;
	int end;
	int inc;
};

#endif
