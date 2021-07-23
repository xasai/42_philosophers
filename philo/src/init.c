#include "philo.h"

void tinfo_init(t_config *cfg)
{
	int				idx;
	int				lmutex_idx;

	idx = 0;
	cfg->tinfo = xmalloc(sizeof(*cfg->tinfo) * cfg->tnum);
	cfg->threads = xmalloc(sizeof(*cfg->threads) * cfg->tnum);
	cfg->mutexes = xmalloc(sizeof(*cfg->mutexes) * cfg->tnum);
	while (idx < (int)cfg->tnum)
	{
		lmutex_idx = idx - 1;
		if (idx == 0)
			lmutex_idx = cfg->tnum - 1;
		cfg->tinfo[idx] = (t_tinfo){
			.id = idx + 1, \
			.tt_die = cfg->tt_die, \
			.tt_eat = cfg->tt_eat, \
			.tt_sleep = cfg->tt_sleep, \
			.iter_max = cfg->iter_max, \
			.iter_completed = &cfg->iter_completed, \
			.f_death = &cfg->f_death, \
			.mutex = &cfg->mutexes[idx], \
			.l_mutex = &cfg->mutexes[lmutex_idx]};
		idx++;
	}
}

t_config	configuration_init(char **av)
{
	uint64_t	*p;
	t_config	cfg;

	cfg = (t_config){.iter_max = -1};
	p = (uint64_t *)&cfg;
	while (*(av + 1) && av++)
		*p++ = _atoi64(*av);
	return (cfg);
}
