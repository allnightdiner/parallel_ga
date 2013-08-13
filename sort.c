#include <stdlib.h>

#include "common.h"
#include "ll.h"

void pop_sort(struct pop_c* pop_conf, struct state** population)
{
	struct node* bins[pop_conf->goal_fit+1];
	struct node* tmp;
	int i,j;
	
	for(i = 0; i < pop_conf->goal_fit+1; bins[i++] = NULL){}

	for(i = 0; i < pop_conf->pop_size; i++)
	{
		bins[population[i]->fitness] = 
		    ll_add(population[i], bins[population[i]->fitness]);
	}
	
	j = 0;
	for(i = pop_conf->goal_fit; i >= 0; i--)
	{
		while(ll_has_next(bins[i]))
		{
			population[j] = bins[i]->data;
			tmp = bins[i];
			bins[i] = bins[i]->next;
			free(tmp);
			j++;
		}		
	}
}


