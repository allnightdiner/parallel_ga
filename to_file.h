#ifndef FILE_TO_FILE
#define FILE_TO_FILE
void mk_ff_plot(struct pop_c* pop_conf);
void mk_af_plot(struct pop_c* pop_conf);
void mk_lg_plot(struct pop_c* pop_conf);
void af_to_file(struct pop_c* pop_conf, struct pop_s* pop_stats);
void ff_to_file(struct pop_c* pop_conf, struct pop_s* pop_stats);
void lg_to_file(struct pop_c* pop_conf, struct pop_s* pop_stats);
void individual_to_file(struct pop_c* pop_conf, int* x, char* file_id);
void pop_to_file(struct pop_c* pop_conf, struct state** pop, char* file_id);

#endif
