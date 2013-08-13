#ifndef FILE_POP_SIM
#define FILE_POP_SIM

int config_dist(struct pop_c* pop_conf, struct state* c1, struct state* c2);
int individual_pop_diff(struct pop_c* pop_conf, struct state** population, 
    int x, int threshold);

#endif
