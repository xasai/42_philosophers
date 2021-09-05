#include "philo.h"

inline bool	should_die(t_thrinfo *ti)
{
	return (get_ms() - ti->ms_last_eat > ti->xdp->tt_die);
}

inline static void	_echo_status(const char *action, t_thrinfo *ti)
{
	if (!ti->xdp->f_death)
		printf("%ld %d %s\n", get_ms() - ti->ms_start, ti->id, action);
}

inline static void	*_die(t_thrinfo *ti)
{
	ti->xdp->workers--;
	if (ti->xdp->f_death)
		return (NULL);
	ti->xdp->f_death = true;
	printf("%ld %d died\n", get_ms() - ti->ms_start, ti->id);
	return (NULL);
}

inline static bool	_eat(t_thrinfo *ti)
{
	pthread_mutex_lock(ti->atomic_mutex);
	pthread_mutex_lock(ti->unatomic_mutex1);
	if (ti->xdp->f_death || should_die(ti))
		return (RETURN_FAILURE);
	_echo_status("has taken a fork", ti);
	pthread_mutex_lock(ti->unatomic_mutex2);
	if (ti->xdp->f_death || should_die(ti))
		return (RETURN_FAILURE);
	_echo_status("has taken a fork", ti);
	_echo_status("is eating", ti);
	ti->ms_last_eat = get_ms();
	if (msleep(ti->xdp->tt_eat, ti))
		return (RETURN_FAILURE);
	pthread_mutex_unlock(ti->atomic_mutex);
	pthread_mutex_unlock(ti->unatomic_mutex1);
	pthread_mutex_unlock(ti->unatomic_mutex2);
	return (RETURN_SUCCESS);
}

void	*thread_entrypoint(void *arg)
{
	int				i;
	t_thrinfo		*t_info;

	i = 0;
	t_info = arg;
	t_info->ms_start = get_ms();
	t_info->ms_last_eat = t_info->ms_start;
	while (!t_info->xdp->f_death && t_info->xdp->max_iter != i)
	{
		_echo_status("is thinking", t_info);
		if (_eat(t_info))
			return (_die(t_info));
		i++;

		//fade i times
		if (t_info->xdp->max_iter == i)
			break ;
		_echo_status("is sleeping", t_info);
		if (msleep(t_info->xdp->tt_sleep, t_info))
			return (_die(t_info));
	}
	t_info->xdp->workers--;
	return (NULL);
}
