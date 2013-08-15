parallel_ga
===========

genetic algorithm that uses pvm distribute its fitness function calculations.

A non PVM version of the GA can be generated with 'make a.out'

No configuration file parsing has been added so changes in the parameters of the GA will need to be made directly to the source files. The function pop_conf_init in pop_init.c controls most of these values. Values of interest are 'n' which is the n in nqueens, 'length_of_run' which determines number of generations, 'cross_rate' and 'mut_rate' which determine the probablility crossover and mutation will occur during the 'reproduction' stage of the GA.  
