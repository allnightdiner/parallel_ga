#ifndef FILE_POP_INIT
#define FILE_POP_INIT

struct state** initilization(struct pop_c* pop_conf, struct state** population);
struct state** null_initilization(struct pop_c* pop_conf, 
    struct state** population);
struct state** 
silly_init(struct pop_c* pop_conf, struct state** population);
void pop_conf_init(struct pop_c* pop_conf);

#endif
