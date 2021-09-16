#include "philo.h"
#include <pthread.h>

#define ALIVE 0 
#define DEATH 1

inline bool	should_die(t_thrinfo *inf)
{
	return (get_ms() - inf->ms_last_eat > inf->xdp->tt_die);
}

inline static void	_echo_status(const char *act, t_thrinfo *inf)
{
	long	time_offset;

	time_offset = get_ms() - inf->ms_start;
	pthread_mutex_lock(inf->w_mutex);
	printf(" %ldms | %2d| %s\n", time_offset, inf->id, act);
	pthread_mutex_unlock(inf->w_mutex);
}

inline static void	*_die(t_thrinfo *inf)
{
	long	time_offset;

	time_offset = inf->ms_start - inf->ms_last_eat + inf->xdp->tt_die + 1;
	inf->xdp->f_death = true;
	pthread_mutex_unlock(inf->atomic_mutex);
	pthread_mutex_unlock(inf->unatomic_mutex1);
	pthread_mutex_unlock(inf->unatomic_mutex2);
	pthread_mutex_lock(inf->w_mutex);
	printf(" %ldms | %2d| died\n", time_offset, inf->id);
	return (NULL);
}

inline static bool	_eat(t_thrinfo *inf)
{
	if (should_die(inf))
		return (DEATH);
	pthread_mutex_lock(inf->atomic_mutex);
	if (should_die(inf))
		return (DEATH);
	pthread_mutex_lock(inf->unatomic_mutex1);
	_echo_status("has taken a fork", inf);
	pthread_mutex_lock(inf->unatomic_mutex2);
	_echo_status("has taken a fork", inf);
	if (should_die(inf))
		return (DEATH);
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
	while (inf->xdp->max_iter != i)
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
