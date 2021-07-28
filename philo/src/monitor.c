#include "philo.h"

void	start_monitoring(t_config *cfg)
{
	while (!cfg->f_death && cfg->iter_completed != cfg->tnum)
	{
		usleep(100);
	}
}

bool should_die(t_tinfo *tinfo)
{
	//return (ms(&tinfo->tv_last_eat) > (uint64_t)tinfo->tt_die);
	//return (get_usec() - to_usec(&tinfo->tv_last_eat) > (tinfo->tt_die * (long)1000));
	return (get_ms() - to_ms(&tinfo->tv_last_eat) > (tinfo->tt_die));
}
