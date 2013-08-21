parallel_ga
===========

genetic algorithm that uses pvm distribute its fitness function calculations.

Requires gnuplot and pvm

No configuration file parsing has been added so changes in the parameters of the GA will need to be made directly to the source files. The function pop_conf_init in pop_init.c controls most of these values. Values of interest are 'n' which is the n in nqueens, 'length_of_run' which determines number of generations, 'cross_rate' and 'mut_rate' which determine the probablility crossover and mutation will occur during the 'reproduction' stage of the GA.  

# Non Parallel Version #

A non PVM version of the GA can be generated with 'make a.out'

first.c covers the main overview of this version. the main function in first.c can be configured to test a wide variety of parameters over multiple populations and generations. Examples of test_conf settings are at the bottom of the file. A particular parameter, start value, end value, and increment value can be configured for a parameter, and then "full runs" of the GA. Graphs are generated for each run of the GA for the full range of values that re being tested. Best Worst and average fitnesses are graphed and placed in a directory name based on the test_id for the test_c struct being used. 

# TODO #

Replace instances of sprintf with snprintf.

Majority of pvm functions do not check return values for error_handling. can lead to garbage in garbage out scenarios between master and slave.
