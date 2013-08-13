#ifndef FILE_FITNESS
#define FILE_FITNESS

int can_kill(int y1,int x1,int y2,int x2);
int non_kill_run(int* x, int start, int length);
int killed_by_none(struct pop_c* pop_conf, int* configuration, int to_test);
void fitness_test(struct pop_c* pop_conf, struct state* to_test);
void population_fitness(struct pop_c* pop_conf, struct state** population);

#endif
