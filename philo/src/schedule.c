#include "philo.h"
#include "t_external_data.h"
#include <pthread.h>

#define DEATH 1 
#define ALIVE 0 

#ifdef _DEBUG

inline static void	
	_launch_workers(int worker_idx, int max_workers, t_external_data *xdp)
{
	int	idx;
	int	thread_idx;

	idx = 0;
	while (idx < max_workers && !xdp->f_death)
	{
		thread_idx = xdp->seq[(worker_idx + idx) % xdp->jobsnum];
		pthread_mutex_unlock(&xdp->atom_muxs[thread_idx]);
		printf("o[%2.d] %ldms | OPEN\n", thread_idx + 1,
			get_ms() - xdp->tinfos[thread_idx].ms_start);
		idx++;
	}
	usleep(xdp->tt_sleep * 500);
	idx = 0;
	while (idx < max_workers)
	{
		thread_idx = xdp->seq[((worker_idx + idx) % xdp->jobsnum)];
		pthread_mutex_lock(&xdp->atom_muxs[thread_idx]);
		printf("x[%2.d] %ldms | LOCK\n", thread_idx + 1,
			get_ms() - xdp->tinfos[thread_idx].ms_start);
		idx++;
	}
}

//if not defined _DEBUG
#else

inline static void	
	_launch_workers(int worker_idx, int max_workers, t_external_data *xdp)
{
	int	idx;
	int	thread_idx;

	idx = 0;
	while (idx < max_workers && !xdp->f_death)
	{
		thread_idx = xdp->seq[(worker_idx + idx) % xdp->jobsnum];
		pthread_mutex_unlock(&xdp->atom_muxs[thread_idx]);
		idx++;
	}
	usleep(xdp->tt_sleep * 500);
	idx = 0;
	while (idx < max_workers)
	{
		thread_idx = xdp->seq[((worker_idx + idx) % xdp->jobsnum)];
		pthread_mutex_lock(&xdp->atom_muxs[thread_idx]);
		idx++;
	}
}

//_DEBUG
#endif

inline bool	should_die(t_thrinfo *inf)
{
	return (get_ms() - inf->ms_last_eat > inf->xdp->tt_die);
}

inline static int	_workers_status(t_external_data *xdp)
{
	if (xdp->threads_done == xdp->jobsnum || xdp->f_death)
		return (DEATH);
	if (xdp->jobsnum != 1)
		return (ALIVE);
	if (should_die(xdp->tinfos))
	{
		printf(" [%2.d] %5.ldms | died (sched)\n", 1, \
				get_ms() - xdp->tinfos->ms_start);
		return (DEATH);
	}
	return (ALIVE);
}

void	*schedule(void *arg)
{
	int				worker_idx;
	int				max_workers;
	t_external_data	*xdp;

	xdp = arg;
	worker_idx = 0;
	max_workers = xdp->jobsnum / 2;
	usleep(500);
	while (_workers_status(xdp) == ALIVE)
	{
		_launch_workers(worker_idx, max_workers, xdp);
		worker_idx = (worker_idx + max_workers) % xdp->jobsnum;
	}
	return (NULL);
}
