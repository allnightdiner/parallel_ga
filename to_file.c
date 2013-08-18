#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "common.h"

void mk_ff_plot(struct pop_c* pop_conf)
{
	int i;
	char file_id[MAX_FILENAME_LEN];
	char cmd[MAX_COMMAND_LEN];
	sprintf(file_id, "%s%dffplot", GRAPH_OUT_DIR, pop_conf->id);
	FILE* out = fopen(file_id, "w");
	fprintf(out, "set terminal png\n");
	fprintf(out, "set xrange [1:%d]\n", pop_conf->length_of_run);
	fprintf(out, "set yrange [0:%d]\n", pop_conf->pop_size);
	fprintf(out, "set output \"%s%dfreq.png\"\n", GRAPH_OUT_DIR,
	    pop_conf->id);
	fprintf(out, "plot ");
	for(i = 0; i < pop_conf->goal_fit; i++)
	{
		fprintf(out, "\"%s%dff\" using 1:%d title \"%d\" with l, ",
		    GRAPH_OUT_DIR, pop_conf->id, i+2, i);
	}
	fprintf(out, "\"%s%dff\" using 1:%d title \"%d\" with l", GRAPH_OUT_DIR,
	    pop_conf->id, i+2, i);
	fclose(out);
	
	sprintf(cmd, "gnuplot %s", file_id); 
	system(cmd);
	
}

void mk_af_plot(struct pop_c* pop_conf)
{
	char file_id[MAX_FILENAME_LEN];
	char cmd[MAX_COMMAND_LEN];
	sprintf(file_id, "%s%dafplot", GRAPH_OUT_DIR, pop_conf->id);
	FILE* out = fopen(file_id, "w");
	fprintf(out, "set terminal png\n");
	fprintf(out, "set xrange [1:%d]\n", pop_conf->length_of_run);
	fprintf(out, "set yrange [0:%d]\n", pop_conf->goal_fit);
	fprintf(out, "set output \"%s%davg.png\"\n", GRAPH_OUT_DIR, 
	    pop_conf->id);
	fprintf(out, "plot ");	
	fprintf(out, "\"%s%daf\" using 1:2 title \"avg\" with l, ", 
	    GRAPH_OUT_DIR, pop_conf->id);
	fprintf(out, "\"%s%daf\" using 1:3 title \"best\" with l, ",
	    GRAPH_OUT_DIR, pop_conf->id);
	fprintf(out, "\"%s%daf\" using 1:4 title \"worst\" with l", 
	    GRAPH_OUT_DIR, pop_conf->id);
	fclose(out);
	
	sprintf(cmd, "gnuplot %s", file_id); 
	system(cmd);
}

void mk_lg_plot(struct pop_c* pop_conf)
{
	char file_id[MAX_FILENAME_LEN];
	char cmd[MAX_COMMAND_LEN];
	sprintf(file_id, "%slgplot", GRAPH_OUT_DIR);
	FILE* out = fopen(file_id, "w");
	fprintf(out, "set terminal png\n");
	fprintf(out, "set xrange [1:%d]\n", pop_conf->n_of_runs);
	fprintf(out, "set yrange [1:%d]\n", pop_conf->length_of_run);
	fprintf(out, "set output \"%slast_generation.png\"\n", GRAPH_OUT_DIR);
	fprintf(out, "plot ");	
	fprintf(out, "%slast_generation using 1:2 title \"lg\"", GRAPH_OUT_DIR);
	fclose(out);
	
	sprintf(cmd, "gnuplot %s", file_id); 
	system(cmd);
		
}

void af_to_file(struct pop_c* pop_conf, struct pop_s* pop_stats)
{
	int i;
	char file_id[MAX_FILENAME_LEN];
	sprintf(file_id, "%s%daf", GRAPH_OUT_DIR, pop_conf->id);
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
	sprintf(file_id, "%s%dff", GRAPH_OUT_DIR, pop_conf->id);
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
	char file_id[MAX_FILENAME_LEN];
	sprintf(file_id, "%slast_generation", GRAPH_OUT_DIR);
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
