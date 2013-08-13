#ifndef FILE_REPRODUCTION
#define FILE_REPRODUCTION

int rand_index(struct pop_c* pop_conf);
void cross_over(struct pop_c* pop_conf, struct state* old_a, struct state* 
    old_b, struct state* new_a, struct state* new_b);
void maintain(struct pop_c* pop_conf, struct state* old_a, struct state* 
    old_b, struct state* new_a, struct state* new_b); 
void mutate(struct pop_c* pop_conf, struct state* to_mutate);
void free_population(struct pop_c* pop_conf, struct state** to_free);
struct state** reproduction(struct pop_c* pop_conf, struct state** population);

#endif
