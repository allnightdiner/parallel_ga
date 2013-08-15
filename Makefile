PVM = -L$(PVM_ROOT)/lib/$(PVM_ARCH) -lpvm3 -I$(PVM_ROOT)/include

master: main_p.c
	gcc -Wall -lm -o $@ ll.c  sort.c from_file.c to_file.c\
	 master_fit.c pop_init.c  reproduction.c stats.c pop_sim.c $+ $(PVM)

slave: slave_fit.c
	gcc -Wall -lm -o $@ $+ $(PVM)

old: main.c
	gcc -Wall -lm -o $@ ll.c  sort.c from_file.c to_file.c fitness.c pop_init.c  reproduction.c stats.c pop_sim.c $+

a.out: first.c
	gcc -Wall -lm -o $@ ll.c  sort.c from_file.c to_file.c fitness.c pop_init.c  reproduction.c stats.c pop_sim.c $+

