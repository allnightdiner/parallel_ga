#include <stdio.h>
#include "common.h"

int config_dist(struct pop_c* pop_conf, struct state* c1, struct state* c2)
{
	int ret = 0;
	int i;
	for(i = 0; i < pop_conf->n; i++)
	{
		if(c1->configuration[i] != c2->configuration[i])
			ret++;
	}	
	return ret;
}

/* There must be a more technical name for this. None of the ones I've
 * thought of are any good.
 * Returns the number of configurations in a population that are below
 * or equal to a certain threshold, in relation to x which is an index
 * for a configuration in a population.
 */
int individual_pop_diff(struct pop_c* pop_conf, struct state** population, 
    int x, int threshold)
{
	int ret = 0;
	int i;
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		if(config_dist(pop_conf, population[x], population[i]) <= 
		    threshold)
		{
			ret++;	
		}
	}
	return ret;
}
