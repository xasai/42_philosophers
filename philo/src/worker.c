#include "philo.h"

#define ALIVE 0 
#define DEATH 1

inline static void	_echo_status(const char *acinfon, t_thrinfo *inf)
{
	if (!inf->xdp->f_death)
		printf("%ld %d %s\n", get_ms() - inf->ms_start, inf->id, acinfon);
}

inline static void	*_die(t_thrinfo *inf)
{
	pthread_mutex_unlock(inf->atomic_mutex);
	pthread_mutex_unlock(inf->unatomic_mutex1);
	pthread_mutex_unlock(inf->unatomic_mutex2);
	if (inf->xdp->f_death)
		return (NULL);
	inf->xdp->f_death = true;
	printf("%ld %d died\n", get_ms() - inf->ms_start, inf->id);
	return (NULL);
}

inline static bool	_eat(t_thrinfo *inf)
{
	pthread_mutex_lock(inf->atomic_mutex);
	pthread_mutex_lock(inf->unatomic_mutex1);
	if (inf->xdp->f_death || should_die(inf))
		return (DEATH);
	_echo_status("has taken a fork", inf);
	pthread_mutex_lock(inf->unatomic_mutex2);
	if (inf->xdp->f_death || should_die(inf))
		return (DEATH);
	_echo_status("has taken a fork", inf);
	_echo_status("is eating", inf);
	inf->ms_last_eat = get_ms();
	if (msleep(inf->xdp->tt_eat, inf))
		return (DEATH);
	pthread_mutex_unlock(inf->atomic_mutex);
	pthread_mutex_unlock(inf->unatomic_mutex1);
	pthread_mutex_unlock(inf->unatomic_mutex2);
	return (ALIVE);
}

void	*thread_entrypoint(void *arg)
{
	int				i;
	t_thrinfo		*inf;

	i = 0;
	inf = arg;
	inf->ms_start = get_ms();
	inf->ms_last_eat = inf->ms_start;
	while (!inf->xdp->f_death && inf->xdp->max_iter != i)
	{
		_echo_status("is thinking", inf);
		if (_eat(inf) == DEATH)
			return (_die(inf));
		i++;
		if (inf->xdp->max_iter == i)
			break ;
		_echo_status("is sleeping", inf);
		if (msleep(inf->xdp->tt_sleep, inf) == DEATH)
			return (_die(inf));
	}
	inf->xdp->threads_done++;
	return (NULL);
}
