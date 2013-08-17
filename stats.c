#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void fit_freq(struct pop_c* pop_conf, struct state** population,
    struct pop_s* pop_stats)
{
	int i;
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		pop_stats->fit_freq[pop_conf->generation]
		    [(population[i])->fitness]++;
	}
}	


void avg_fit(struct pop_c* pop_conf, struct state** population, struct pop_s*
    pop_stats)
{
	int i;
	int avg = 0;

	for(i = 0; i < pop_conf->pop_size; i++)
	{
		avg += population[i]->fitness;
	}
	(pop_stats->avg_fit)[pop_conf->generation] += avg/pop_conf->pop_size;
	(pop_stats->best_fit)[pop_conf->generation] += population[0]->fitness;
	(pop_stats->worst_fit)[pop_conf->generation] += 
	    population[pop_conf->pop_size-1]->fitness;

}

void stats_init(struct pop_c* pop_conf, struct pop_s* pop_stats)
{
	int i, j;
	int x = pop_conf->length_of_run;
	int y = pop_conf->n_of_runs;
	pop_stats->avg_fit = malloc(sizeof(int)*x);
	pop_stats->best_fit = malloc(sizeof(int)*x);
	pop_stats->worst_fit = malloc(sizeof(int)*x);
	pop_stats->fit_freq = malloc(sizeof(unsigned int*)*x);
	pop_stats->last_generation = malloc(sizeof(int)*y);
	
	for(i = 0; i < x; i++)
	{
		pop_stats->avg_fit[i] = 0;
		pop_stats->best_fit[i] = 0;
		pop_stats->worst_fit[i] = 0;
		pop_stats->fit_freq[i] = malloc(sizeof(unsigned int) *
		    pop_conf->goal_fit+1);
		for(j = 0; j < pop_conf->goal_fit+1; j++)
			pop_stats->fit_freq[i][j] = 0;

	}
	for(i = 0; i < y; pop_stats->last_generation[i++] = 0);
}

void clear_stats(struct pop_c* pop_conf, struct pop_s* pop_stats)
{
	int i, j;
	for(i = 0; i < pop_conf->length_of_run; i++)
	{
		pop_stats->avg_fit[i] = 0;
		pop_stats->best_fit[i] = 0;
		pop_stats->worst_fit[i] = 0;
		for(j = 0; j < pop_conf->goal_fit+1; j++)
			pop_stats->fit_freq[i][j] = 0;

	}
}

void free_stats(struct pop_c* pop_conf, struct pop_s* to_free)
{
	free(to_free->avg_fit);
	free(to_free->best_fit);
	free(to_free->worst_fit);
	free(to_free->last_generation);
	
	int i;
	for(i = 0; i < pop_conf->length_of_run; i++)
		free(to_free->fit_freq[i]);

	free(to_free->fit_freq);
	free(to_free);	
}

void avg_all_af(struct pop_c* pop_conf, struct pop_s* pop_stats, int x)
{
	int i, j;
	int tmp_a, tmp_b, tmp_w;
	char file_id[20];
	for(i = 1; i <= x; i++)
	{
		sprintf(file_id, "%daf", i);
		FILE* in = fopen(file_id, "r");
		while(!feof(in))
		{
			fscanf(in, "%d %d %d %d", &j, &tmp_a, &tmp_b, &tmp_w); 
			pop_stats->avg_fit[j] += tmp_a;
			pop_stats->best_fit[j] += tmp_b;
			pop_stats->worst_fit[j] += tmp_w;
		}
		fclose(in);
	}
	for(i = 0; i < pop_conf->length_of_run; i++)
	{
		pop_stats->avg_fit[i] /= x;
		pop_stats->best_fit[i] /= x;
		pop_stats->worst_fit[i] /= x;
	}

}

void avg_all_ff(struct pop_c* pop_conf, struct pop_s* pop_stats, int x)
{
	int i, j, k;
	int tmp;
	char file_id[20];
	for(i = 1; i <= x; i++)
	{
		sprintf(file_id, "%dff", i);
		FILE* in = fopen(file_id, "r");
		while(!feof(in))
		{
			fscanf(in, "%d", &k);
			for(j = 0; j <= pop_conf->goal_fit; j++)
			{
				fscanf(in, "%d", &tmp); 
				pop_stats->fit_freq[k][j] += tmp;
			}
		}
		fclose(in);
	}
	for(i = 0; i < pop_conf->length_of_run; i++)
	{
		for(j = 0; j <= pop_conf->goal_fit; j++)
		{
			pop_stats->fit_freq[i][j] /= x;
		}
	}
}

/* avg_a, avg_b, avg_w appear to be unitialized. Function has no references in
 * code base commenting out function to stop compiler warnings. 
 */
void std_dev_af(struct pop_c* pop_conf, struct pop_s* pop_stats, int x)
{
/*
	int i, j;
	int tmp_a, tmp_b, tmp_w, tmp;
	int avg_a, avg_b, avg_w;
	char file_id[20];
	FILE** ins = malloc(sizeof(FILE*)*x+1);
	for(i = 1; i <= x; i++)
	{
		sprintf(file_id, "%daf", x);
		ins[i] = fopen(file_id, "r");
	}

	for(i = 0; i < pop_conf->length_of_run; i++)
	{
		for(j = 1; j < x+1; j++)
		{
			fscanf(ins[j], "%d %d %d %d", &tmp, &tmp_a, &tmp_b, 
			    &tmp_w);
			pop_stats->avg_fit[i] += (pow(abs(tmp_a - avg_a), 2));
			pop_stats->best_fit[i] += (pow(abs(tmp_b - avg_b), 2));
			pop_stats->worst_fit[i] += (pow(abs(tmp_w - avg_w), 2));
		}
	}
	for(i = 0; i < pop_conf->length_of_run; i++)
	{
		pop_stats->avg_fit[i] = sqrt(pop_stats->avg_fit[i]/x);
		pop_stats->best_fit[i] = sqrt(pop_stats->best_fit[i]/x);
		pop_stats->worst_fit[i] = sqrt(pop_stats->worst_fit[i]/x);
	}
*/
}

int avg_lg(struct pop_c* pop_conf, struct pop_s* pop_stats)
{
	int i;
	int ret = 0;
	for(i = 0; i < pop_conf->n_of_runs; i++)
		ret += pop_stats->last_generation[i];

	ret /= pop_conf->n_of_runs;
	return ret;
}
