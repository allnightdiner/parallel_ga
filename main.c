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
void 
full_run(struct pop_c* pop_conf, struct pop_s* pop_stats, char* to_file_id)
{
	pop_conf->generation = 0;
	struct state** population;
	int seed = clock() + rand() + (unsigned int) time(NULL);
	srand(seed);		

	
	/* 
	int neighbors[NUM_NODES];
	pvm_init(neighbors); 
	*/

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

		/*
		if (should i migrate?)
			migrate(pop_conf, population, neighbors);

		merge(pop_conf, population, neighbors);
		 */

		pop_conf->generation++;
	}

	individual_to_file(pop_conf,(population[0])->configuration, to_file_id);
	
	free_population(pop_conf, population);
}

int
main(int argc, char** argv)
{
	struct pop_c* pop_conf = malloc(sizeof(struct pop_c));
	pop_conf_init(pop_conf);
	struct pop_s* pop_stats = malloc(sizeof(struct pop_s));

	char* cross_id = "crossover";	
	
	full_run(pop_conf, pop_stats, cross_id);

	return 0;
}

