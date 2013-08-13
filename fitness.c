#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int can_kill(int y1,int x1,int y2,int x2)
{
	if((abs(y1-y2) == abs(x1-x2)) || (x1 == x2) || (y1 == y2))
		return 1;
	return 0;
}

int non_kill_run(int* x, int start, int length)
{
	int i;
	for(i = start; i < (start + length); i++)
	{
		if(can_kill(x[i], i, x[start +
		     length], (start + length)))
		{
			return 0;
		}
	}
	return 1;
}

int killed_by_none(struct pop_c* pop_conf, int* configuration, int to_test)
{
	int i;
	for(i = 0; i < pop_conf->n; i++)
	{
		if(i != to_test && can_kill(configuration[i], i, 
		    configuration[to_test], to_test))
			return 0;
	}
	return 1;
}

void fitness_test(struct pop_c* pop_conf, struct state* to_test)
{
	int i, j;
	int tmp_fit = 0;
	int kill_flag;

	for(i = 0; i < (pop_conf->n); i++)
	{
		kill_flag = 0;
		for(j = i; j < pop_conf->n; j++)
		{
			if((i != j) && can_kill(to_test->configuration[i], i, 
			    to_test->configuration[j], j))
			{
				kill_flag = 1;
				break;	
			}
		}
		if(!kill_flag)
			tmp_fit++;
	}

	to_test->fitness = tmp_fit;
}

void population_fitness(struct pop_c* pop_conf, struct state** population)
{
	int i;
	for(i = 0; i < pop_conf->pop_size; i++)
		fitness_test(pop_conf, population[i]);

}
