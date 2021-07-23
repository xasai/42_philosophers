#include "philo.h"

void tinfo_init(t_config *cfg)
{
	long			idx;
	int				lmutex_idx;

	idx = 0;
	cfg->tinfo = xmalloc(sizeof(*cfg->tinfo) * cfg->args.tnum);
	cfg->threads = xmalloc(sizeof(*cfg->threads) * cfg->args.tnum);
	cfg->mutexes = xmalloc(sizeof(*cfg->mutexes) * cfg->args.tnum);
	while (idx < cfg->args.tnum)
	{
		lmutex_idx = idx - 1;
		if (idx == 0)
			lmutex_idx = cfg->args.tnum - 1;
		cfg->tinfo[idx] = (t_tinfo){
			.id = idx + 1, \
			.args = &cfg->args, \
			.iter_completed = &cfg->iter_completed, \
			.f_death = &cfg->f_death, \
			.mutex = &cfg->mutexes[idx], \
			.l_mutex = &cfg->mutexes[lmutex_idx] \
		};
		idx++;
	}
}

t_config	configuration_init(char **av)
{
	long		*p;
	t_config	cfg;

	cfg = (t_config){.args.iter_max = -1};
	p = (long *)&cfg;
	while (*(av + 1) && av++)
		*p++ = _atol(*av);
	return (cfg);
}
