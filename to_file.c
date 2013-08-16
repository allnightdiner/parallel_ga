#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void mk_ff_plot(struct pop_c* pop_conf)
{
	int i;
	char file_id[MAX_FILENAME_LEN];
	char cmd[30];
	sprintf(file_id, "%dffplot", pop_conf->id);
	FILE* out = fopen(file_id, "w");
	fprintf(out, "set terminal png\n");
	fprintf(out, "set xrange [1:%d]\n", pop_conf->length_of_run);
	fprintf(out, "set yrange [0:%d]\n", pop_conf->pop_size);
	fprintf(out, "set output \"%dfreq.png\"\n", pop_conf->id);
	fprintf(out, "plot ");	
	for(i = 0; i < pop_conf->goal_fit; i++)
	{
		fprintf(out, "\"%dff\" using 1:%d title \"%d\" with l, ",
		    pop_conf->id, i+2, i);
	}
	fprintf(out, "\"%dff\" using 1:%d title \"%d\" with l",
	    pop_conf->id, i+2, i);
	fclose(out);
	
	sprintf(cmd, "gnuplot %s", file_id); 
	system(cmd);
		
}

void mk_af_plot(struct pop_c* pop_conf)
{
	char file_id[MAX_FILENAME_LEN];
	char cmd[30];
	sprintf(file_id, "%dafplot", pop_conf->id);
	FILE* out = fopen(file_id, "w");
	fprintf(out, "set terminal png\n");
	fprintf(out, "set xrange [1:%d]\n", pop_conf->length_of_run);
	fprintf(out, "set yrange [0:%d]\n", pop_conf->goal_fit);
	fprintf(out, "set output \"%davg.png\"\n", pop_conf->id);
	fprintf(out, "plot ");	
	fprintf(out, "\"%daf\" using 1:2 title \"avg\" with l, ", pop_conf->id);
	fprintf(out, "\"%daf\" using 1:3 title \"best\" with l, ",pop_conf->id);
	fprintf(out, "\"%daf\" using 1:4 title \"worst\" with l", pop_conf->id);
	fclose(out);
	
	sprintf(cmd, "gnuplot %s", file_id); 
	system(cmd);
}

void mk_lg_plot(struct pop_c* pop_conf)
{
	char file_id[MAX_FILENAME_LEN];
	char cmd[30];
	sprintf(file_id, "lgplot");
	FILE* out = fopen(file_id, "w");
	fprintf(out, "set terminal png\n");
	fprintf(out, "set xrange [1:%d]\n", pop_conf->n_of_runs);
	fprintf(out, "set yrange [1:%d]\n", pop_conf->length_of_run);
	fprintf(out, "set output \"last_generation.png\"\n");
	fprintf(out, "plot ");	
	fprintf(out, "last_generation using 1:2 title \"lg\"");
	fclose(out);
	
	sprintf(cmd, "gnuplot %s", file_id); 
	system(cmd);
		
}

void af_to_file(struct pop_c* pop_conf, struct pop_s* pop_stats)
{
	int i;
	char file_id[MAX_FILENAME_LEN];
	sprintf(file_id, "%daf", pop_conf->id);
	FILE* out = fopen(file_id, "w");
	for(i = 0; i < pop_conf->length_of_run; i++)
	{
		fprintf(out,"%d %d %d %d\n", i, pop_stats->avg_fit[i],
		    pop_stats->best_fit[i], pop_stats->worst_fit[i]); 
	}
	fclose(out);
	mk_af_plot(pop_conf);
}

void ff_to_file(struct pop_c* pop_conf, struct pop_s* pop_stats)
{
	int i, j;
	char file_id[MAX_FILENAME_LEN];
	sprintf(file_id, "%dff", pop_conf->id);
	FILE* out = fopen(file_id, "w");
	for(i = 0; i < pop_conf->length_of_run; i++)
	{
		fprintf(out, "%d ", i);
		for(j = 0; j <= pop_conf->goal_fit; j++)
			fprintf(out, "%d ", (pop_stats->fit_freq)[i][j]);
		fprintf(out, "\n");
	}
	fclose(out);
	mk_ff_plot(pop_conf);
}

void lg_to_file(struct pop_c* pop_conf, struct pop_s* pop_stats)
{
	int i;
	char* file_id = "last_generation";
	FILE* out = fopen(file_id, "w");
	for(i = 0; i < pop_conf->n_of_runs; i++)
	{
		fprintf(out, "%d %d\n", i, pop_stats->last_generation[i]);
	}
	fclose(out);
	mk_af_plot(pop_conf);
}

void individual_to_file(struct pop_c* pop_conf, int* x, char* file_id)
{
	int i;
	FILE* out = fopen(file_id, "a");
	for(i = 0; i < pop_conf->n; i++)
		fprintf(out, "%d ", x[i]);	
	
	fprintf(out, "\n");
	fclose(out);
}

void 
pop_to_file(struct pop_c* pop_conf, struct state** pop, char* file_id)
{
	int i, j;
	FILE* out = fopen(file_id, "a");
	for(i = 0; i < pop_conf->pop_size; i++)
	{
		for(j = 0; j < pop_conf->n; j++)
			fprintf(out, "%d ", (pop[i])->configuration[j]);	
		fprintf(out, "\n");
	}
}
