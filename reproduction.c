#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "common.h"
#include "fitness.h"
#include "pop_init.h"
#include "reproduction.h"
#include "ll.h"

int rand_index(struct pop_c* pop_conf)
{
	int ret;
	int i;
	int idk = 0;
	//ret = rand()%pop_conf->sum;
	ret = R(pop_conf->sum);

	for(i = 0; i <= pop_conf->pop_size; i++)
	{
		if((ret >= idk) && (ret <= idk + (pop_conf->pop_size - i)))
			return i;
		else
			idk += pop_conf->pop_size - i;
	}
	printf("RADOM INDEX FAILURE\n");
	return 0;
}

void cross_over(struct pop_c* pop_conf, struct state* old_a, struct state* 
    old_b, struct state* new_a, struct state* new_b)
{
	int i;

	if(R(1000) < pop_conf->cross_rate)
	{
		for(i = 0; i < pop_conf->n; i++)	
		{
			if(R(2))
			{
				new_a->configuration[i] = 
				    old_a->configuration[i];
				new_b->configuration[i] = 
				    old_b->configuration[i];
			}
			else
			{
				new_a->configuration[i] = 
				    old_b->configuration[i];
				new_b->configuration[i] = 
				    old_a->configuration[i];
			}
		}

	}
	else
		maintain(pop_conf, old_a, old_b, new_a, new_b);
}

void maintain(struct pop_c* pop_conf, struct state* old_a, struct state* 
    old_b, struct state* new_a, struct state* new_b) 
{
	 int i;
	for(i = 0; i < pop_conf->n; i++)
	{
		new_a->configuration[i] = old_a->configuration[i];
		new_b->configuration[i] = old_b->configuration[i];
	}

}

void mutate(struct pop_c* pop_conf, struct state* to_mutate)
{
	int i;
	for(i = 0; i < pop_conf->n; i++)
	{
		if(R(1000) < pop_conf->mut_rate)
			to_mutate->configuration[i] = R(pop_conf->n);
	}
}

void free_population(struct pop_c* pop_conf, struct state** to_free)
{
	int i;
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		free(to_free[i]->configuration);
		free(to_free[i]);
	}
	free(to_free);
}

struct state** reproduction(struct pop_c* pop_conf, struct state** population)
{
	int i;
	struct state** new_population;
	new_population = null_initilization(pop_conf, new_population);

	for(i = 0; i < pop_conf->pop_size-1; i = i+2)
	{
		cross_over(pop_conf, population[rand_index(pop_conf)], 
		    population[R(pop_conf->pop_size)],new_population[i], 
		    new_population[i+1]); 
	}
	
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		mutate(pop_conf, new_population[i]);
	}
	
	free_population(pop_conf, population);

	return new_population;
}

