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

#include "common.h"
#include "pvm3.h"

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

int killed_by_none(int n, int* configuration, int to_test)
{
	int i;
	for(i = 0; i < n; i++)
	{
		if(i != to_test && can_kill(configuration[i], i, 
		    configuration[to_test], to_test))
			return 0;
	}
	return 1;
}

int fitness_test(int n, int* configuration)
{
	int i, j;
	int tmp_fit = 0;
	int kill_flag;

	for(i = 0; i < n; i++)
	{
		kill_flag = 0;
		for(j = i; j < n; j++)
		{
			if((i != j) && can_kill(configuration[i], i, 
			    configuration[j], j))
			{
				kill_flag = 1;
				break;	
			}
		}
		if(!kill_flag)
			tmp_fit++;
	}

	return  tmp_fit;
}
int
main(int argc, char* argv[])
{
	int my_tid;
	int sender_id;
	int n;
	int num_of_configs;
	int config_id;
	int* config;
	int config_fit;
	int master_id = pvm_parent();
	
	//printf("im a kid %d\n", master_id);
	my_tid = pvm_mytid();
	pvm_recv(-1, -1);
	pvm_upkint(&num_of_configs, 1, 1);
	pvm_upkint(&n, 1, 1);
	//printf("tid=%d; %d %d\n", my_tid, num_of_configs, n);
	//fflush(stdout);
	
	config = malloc(sizeof(int) * n);

	/* a failure on the second upkint would be srsly dangerous as config is
	 * uncleared malloced memory. I don't know what to do... */
	int i;
	pvm_recv(-1, -1);
	for (i = 0; i < num_of_configs; i++)
	{
		pvm_upkint(&config_id, 1, 1);
		pvm_upkint(config, n, 1);

		config_fit = fitness_test(n, config);
		
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&config_id, 1, 1);
		pvm_pkint(&config_fit, 1, 1);
		pvm_send(master_id, 0);
	}
	pvm_exit();
	return 1;	
}
