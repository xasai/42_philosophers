#include "philo.h"

void	start_monitoring(t_config *cfg)
{
	while (!cfg->f_death && cfg->iter_completed != cfg->args.tnum)
		usleep(1000);
}

inline bool should_die(t_tinfo *tinfo)
{
	long	now;

	now = get_ms();
	return (tinfo->args->tt_die < now - tinfo->ms_last_eat);
}
