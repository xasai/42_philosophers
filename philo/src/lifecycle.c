#include "philo.h"

inline static void _echo_status(const char *action, t_tinfo *tinfo)
{
	printf("%ld %ld %s\n", ms(&tinfo->tv_start), tinfo->id, action);
}

inline static void *die(t_tinfo *tinfo)
{
	if (*tinfo->f_death)
		return (NULL);
	_echo_status("died", tinfo);
	printf("from last eat %ld \n", ms(&tinfo->tv_last_eat));
	*tinfo->f_death = true;
	return (NULL);
}

inline static bool _take_forks(t_tinfo *tinfo)
{	
	pthread_mutex_lock(tinfo->l_mutex);
	if (*tinfo->f_death || should_die(tinfo))
		return (RETURN_FAILURE);
	_echo_status("has taken a fork", tinfo);
	pthread_mutex_lock(tinfo->mutex);
	if (*tinfo->f_death || should_die(tinfo))
		return (RETURN_FAILURE);
	_echo_status("has taken a fork", tinfo);
	return (RETURN_SUCCESS);
}

inline static bool _eat(t_tinfo *tinfo)
{
	if (should_die(tinfo) || _take_forks(tinfo))
		return (RETURN_FAILURE);
	_echo_status("is eating", tinfo);
	gettimeofday(&tinfo->tv_last_eat, NULL);
	if (msleep(tinfo->tt_eat, tinfo))
		return (RETURN_FAILURE);
	pthread_mutex_unlock(tinfo->l_mutex);
	pthread_mutex_unlock(tinfo->mutex);
	return (RETURN_SUCCESS);
}

void	*lifecycle_start(void *arg)
{
	t_tinfo	*tinfo;

	tinfo = arg;
	tinfo->tv_last_eat = tinfo->tv_start;
	while (!*tinfo->f_death && tinfo->iter_max)
	{
		_echo_status("is thinking", tinfo);
		if (*tinfo->f_death || _eat(tinfo) || should_die(tinfo))
			return (die(tinfo));
		if (*tinfo->f_death)
			return (NULL);
		_echo_status("is sleeping", tinfo);
		if (msleep(tinfo->tt_sleep, tinfo))
			return (die(tinfo));
		if (tinfo->iter_max != -1)
			tinfo->iter_max--;
	}
	*tinfo->iter_completed += 1;
	return (NULL);
}
