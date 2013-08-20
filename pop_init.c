#include <stdlib.h>

#include "common.h"

struct state** 
initilization(struct pop_c* pop_conf, struct state** population)
{
	int i,j;	

	population = malloc(sizeof(struct state*) * pop_conf->pop_size);
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		population[i] = malloc(sizeof(struct state));
		population[i]->configuration = malloc(sizeof(int)*pop_conf->n);
		for(j = 0; j < pop_conf->n; j++)
		{
			population[i]->configuration[j] = (R(pop_conf->n));
		}
		population[i]->fitness = 0;
	}
	return population;
}

struct state** 
null_initilization(struct pop_c* pop_conf, struct state** population)
{
	int i;	

	population = malloc(sizeof(struct state*)*pop_conf->pop_size);
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		population[i] = malloc(sizeof(struct state));
		population[i]->configuration = malloc(sizeof(int)*pop_conf->n);
		population[i]->fitness = 0;
	}
	return population;
}


struct state** 
silly_init(struct pop_c* pop_conf, struct state** population)
{
	int i,j;	
	int used[8] = {0};
	int randy;
	population = malloc(sizeof(struct state*)*pop_conf->pop_size);
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		population[i] = malloc(sizeof(struct state));
		population[i]->configuration = malloc(sizeof(int)*pop_conf->n);
		for(j = 0; j < pop_conf->n; j++)
		{
			while(used[randy = R(pop_conf->n)]);
			population[i]->configuration[j] = randy;
			used[randy] = 1;
		}
		population[i]->fitness = 0;
	}
	return population;
}

void pop_conf_init(struct pop_c* pop_conf)
{
	pop_conf->id = 0;
	pop_conf->pop_size = 50;
	pop_conf->n = 8;
	pop_conf->generation = 0;
	pop_conf->length_of_run = 20;
	pop_conf->sum = ((pop_conf->pop_size * pop_conf->pop_size) + 
	    pop_conf->pop_size)/2;
	pop_conf->goal_fit = pop_conf->n;
	//all rates are per 1000
	pop_conf->cross_rate = 700;
	pop_conf->mut_rate = 2;
	pop_conf->n_of_runs = 5;
}
