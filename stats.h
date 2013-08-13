#ifndef FILE_STATS
#define FILE_STATS


void fit_freq(struct pop_c* pop_conf, struct state** population,
    struct pop_s* pop_stats);
void avg_fit(struct pop_c* pop_conf, struct state** population, struct pop_s*
    pop_stats);
void stats_init(struct pop_c* pop_conf, struct pop_s* pop_stats);
void clear_stats(struct pop_c* pop_conf, struct pop_s* pop_stats);
void free_stats(struct pop_c* pop_conf, struct pop_s* to_free);
void avg_all_af(struct pop_c* pop_conf, struct pop_s* pop_stats, int x);
void avg_all_ff(struct pop_c* pop_conf, struct pop_s* pop_stats, int x);
void std_dev_af(struct pop_c* pop_conf, struct pop_s* pop_stats, int x);
int avg_lg(struct pop_c* pop_conf, struct pop_s* pop_stats);

#endif
