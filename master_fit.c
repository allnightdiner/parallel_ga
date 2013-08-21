#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/queue.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "pvm3.h"

#include "common.h"

#define MAXNCHILD 1

void 
population_fitness(struct pop_c* pop_conf, struct state** population)
{

	int ntask = MAXNCHILD;
	int info;
	int mytid;
	int child[MAXNCHILD];
	int i, j;
	mytid = pvm_mytid();

	if (mytid < 0) 
	{ 
		/* the perneially informative error message of my youth. */
		pvm_perror("wat"); 
		exit(-1);
	}

	/* spawn the child tasks */
	info = pvm_spawn("/home/rwblair/projects/parallel_ga/slave", (char**)0, 
	    PvmTaskDefault, (char*)0, ntask, child);
	/* only proceeds if all children properly spawned. It doesn't have to be
	 * this way but its easiest
	 */
	printf("result of pvm_spawn call: %d\n", info);
	printf("value of first index of child array: %d\n", child[0]);
	if (info != ntask) 
	{
		pvm_exit(); 
		exit(-1);
	}
	
	int tmp;	
	for (i = 0; i < ntask; i++)
	{
		tmp = ((pop_conf->pop_size)/ntask);
		if (i < (pop_conf->pop_size % ntask))
			tmp++;
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&tmp, 1, 1);
		pvm_pkint(&(pop_conf->n), 1, 1);
		info = pvm_send(child[i], 0);
	}
	
	j = 0;
	for (i = 0; i < pop_conf->pop_size; i++) 
	{
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&i, 1, 1);
		pvm_pkint(population[i]->configuration, pop_conf->n, 1);

		if ((i == pop_conf->pop_size -1) || 
		    (((pop_conf->pop_size / MAXNCHILD)) * (j + 1)) - 1 == i)
		{
			info = pvm_send(child[j++], 0);
		}
	}


	int recv_ret;
	int recv_index;	
	int recv_fit;
	/* error handling, if a given thing fucks up how can it be unfucked? */
	for (i = 0; i < pop_conf->pop_size; i++)
	{
		recv_ret = pvm_recv(-1, -1);
		pvm_upkint(&recv_index, 1, 1);
		pvm_upkint(&recv_fit, 1, 1);	
		printf("recieved fitness: %d\n", recv_fit);
		population[recv_index]->fitness = recv_fit;
		/*
		if ((recv_index < 0) || (recv_index >= pop_conf->pop_size))
			printf("BAD RECV_INDEX\n");
		*/
	}

	pvm_exit();
	return;

}
