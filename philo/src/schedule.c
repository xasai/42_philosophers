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
		thread_idx = xdp->seq[(worker_idx + idx) % xdp->threads_num];
		pthread_mutex_unlock(&xdp->atom_muxs[thread_idx]);
		printf(" %ldms | %d | oooooo OPEN oooooo\n",
			get_ms() - xdp->tinfos[thread_idx].ms_start, thread_idx + 1);
		idx++;
	}
	usleep(xdp->tt_sleep * 500);
	idx = 0;
	while (idx < max_workers)
	{
		thread_idx = xdp->seq[((worker_idx + idx) % xdp->threads_num)];
		pthread_mutex_lock(&xdp->atom_muxs[thread_idx]);
		printf(" %ldms | %d | xxxxxx CLOSE xxxxxx\n",
			get_ms() - xdp->tinfos[thread_idx].ms_start, thread_idx + 1);
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
		thread_idx = xdp->seq[(worker_idx + idx) % xdp->threads_num];
		pthread_mutex_unlock(&xdp->atom_muxs[thread_idx]);
		idx++;
	}
	usleep(xdp->tt_sleep * 500);
	idx = 0;
	while (idx < max_workers)
	{
		thread_idx = xdp->seq[((worker_idx + idx) % xdp->threads_num)];
		pthread_mutex_lock(&xdp->atom_muxs[thread_idx]);
		idx++;
	}
}

//_DEBUG
#endif

inline static int	_workers_status(t_external_data *xdp)
{
	if (xdp->threads_done == xdp->threads_num || xdp->f_death)
		return (DEATH);
	if (xdp->threads_num != 1)
		return (ALIVE);
	while (!should_die(xdp->tinfos))
		usleep(100);
	printf(" %ldms | %2d| died\n", get_ms() - xdp->tinfos->ms_start, 1);
	xdp->f_death = true;
	return (DEATH);
}

void	*schedule(void *arg)
{
	int				worker_idx;
	int				max_workers;
	t_external_data	*xdp;

	xdp = arg;
	worker_idx = 0;
	max_workers = xdp->threads_num / 2;
	usleep(100);
	while (_workers_status(xdp) == ALIVE)
	{
		_launch_workers(worker_idx, max_workers, xdp);
		worker_idx = (worker_idx + max_workers) % xdp->threads_num;
	}
	return (NULL);
}
