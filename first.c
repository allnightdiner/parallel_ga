#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "common.h"
#include "fitness.h"
#include "pop_init.h"
#include "pop_sim.h"
#include "reproduction.h"
#include "sort.h"
#include "stats.h"
#include "from_file.h"
#include "to_file.h"

#define GRAPH_OUT_DIR "./graphs"

void
full_run(struct pop_c* pop_conf, struct pop_s* pop_stats, char* to_file_id)
{
	pop_conf->generation = 0;
	struct state** population;
	int seed = clock() + rand() + (unsigned int) time(NULL);
	srand(seed);		


	population = initilization(pop_conf, population);
	population_fitness(pop_conf, population);
	pop_sort(pop_conf, population);
	
	while(pop_conf->generation < pop_conf->length_of_run && 
	    population[0]->fitness != pop_conf->goal_fit)
	{
		if(seed	!= (unsigned int)time(NULL))
		{
			seed = (unsigned int)time(NULL);
			srand(seed);	
		}

		population = reproduction(pop_conf, population);
		population_fitness(pop_conf, population);
		pop_sort(pop_conf, population);

		avg_fit(pop_conf, population, pop_stats);
		fit_freq(pop_conf, population, pop_stats);

		pop_conf->generation++;
	}

	pop_stats->last_generation[pop_conf->id] = pop_conf->generation;
	if(population[0]->fitness >= pop_conf->goal_fit)
	{
		individual_to_file(pop_conf,(population[0])->configuration, 
		    to_file_id);
	}
	free_population(pop_conf, population);
}

void multiple_runs(struct pop_c* pop_conf, char* file_id)
{
	struct pop_s* pop_stats = malloc(sizeof(struct pop_s));
	stats_init(pop_conf, pop_stats);
	int i;
	pop_conf->id = 0;
	for(i = 0; i < pop_conf->n_of_runs; i++)
	{
		printf("run %d\n", i);
		pop_conf->id = i;
		full_run(pop_conf, pop_stats, file_id);	
		af_to_file(pop_conf, pop_stats);
		ff_to_file(pop_conf, pop_stats);
		clear_stats(pop_conf, pop_stats);
	}
	free_stats(pop_conf, pop_stats);
}

void 
test(struct pop_c* pop_conf, struct test_c* test_conf)
{
	int* i = test_conf->to_test;
	char file_id[40];
	char cmd[80];
	char dir[40];
	sprintf(cmd, "rm -r %s%s", GRAPH_OUT_DIR, test_conf->test_id);
	sprintf(cmd, "mkdir %s%s", GRAPH_OUT_DIR, test_conf->test_id);
	system(cmd);

	for(*i = test_conf->start; *i <= test_conf->end; *i += test_conf->inc)
	{
		
		sprintf(file_id, "%s_%d_solutions", test_conf->test_id, *i); 
		multiple_runs(pop_conf, file_id);

		sprintf(dir, "%s%s/%d", GRAPH_OUT_DIR, test_conf->test_id, *i);
		sprintf(cmd, "mkdir %s", dir);
		system(cmd);
		sprintf(cmd, "mv *.png %s %s", file_id, dir);
		system(cmd);
		system("rm *f *plot");
	}
}

int
main(int argc, char** argv)
{
	struct pop_c* pop_conf = malloc(sizeof(struct pop_c));
	pop_conf_init(pop_conf);
	struct test_c* test_conf = malloc(sizeof(struct test_c));

	char* cross_id = "crossover";	

	/* test crossover rates */
	test_conf->test_id = cross_id;
	test_conf->to_test = &(pop_conf->cross_rate);
	test_conf->start = 0;
	test_conf->end = 1000;
	test_conf->inc = 100;

	test(pop_conf, test_conf);
	return 0;
}



	/* Now that runs can end early stats functions need to be rewritten
	pop_conf->id++; 
	avg_all_af(pop_conf, pop_stats, x);
	avg_all_ff(pop_conf, pop_stats, x);
	af_to_file(pop_conf, pop_stats);
	ff_to_file(pop_conf, pop_stats);
	*/

	/*
	char* mut_id = "mutation";
	char* pop_size_id = "pop_size";
	char* n_id = "NxN";
	*/

	/* test mutation rates 
	test_conf->mut_id;
	test_conf->i = &(pop_conf->mut_rate);
	test_conf->start = 0;
	test_conf->end = 20;
	test_conf->inc = 2;
	*/

	/* test population sizes 
	test_conf->pop_size_id;
	test_conf->i = &(pop_conf->pop_size);
	test_conf->start = 25;
	test_conf->end = 300;
	test_conf->inc = 25;
	*/

	/* test N 
	test_conf->n_id;
	test_conf->i = &(pop_conf->n);
	test_conf->start = 8;
	test_conf->end = 20;
	test_conf->inc = 1;
	*/
