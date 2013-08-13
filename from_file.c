#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void 
pop_from_file(struct pop_c* pop_conf, struct state** population, char* file_id)
{
	int i, j;
	FILE* in = fopen(file_id, "r");
	
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		for(j = 0; j < (pop_conf->n); j++)
		{
			fscanf(in, "%d ", &((population[i])->configuration[j]));
		}
		fscanf(in,"\n");
	}
}
