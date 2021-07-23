#include "philo.h"

void	start_monitoring(t_config *cfg)
{
	while (!cfg->f_death && cfg->iter_completed != cfg->tnum)
	{
		usleep(10000);
	}
}

bool should_die(t_tinfo *tinfo)
{
	return (ms(&tinfo->tv_last_eat) > (uint64_t)tinfo->tt_die);
}
