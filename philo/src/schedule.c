#include "philo.h"

#define DEATH 1 
#define ALIVE 0 

inline static void	
_launch_workers(int worker_idx, int max_workers, t_external_data *xdp)
{
	int	idx;
	int	thread_idx;

	idx = 0;
	while (idx < max_workers)
	{
		thread_idx = xdp->seq[(worker_idx + idx) % xdp->jobsnum];
		pthread_mutex_unlock(&xdp->atom_muxs[thread_idx]);
		printf("ALLOWED ===>%d\n", thread_idx+1);
		idx++;
	}
	usleep(200);
	idx= 0;
	while (idx < max_workers)
	{
		thread_idx = xdp->seq[((worker_idx + idx) % xdp->jobsnum)];
		pthread_mutex_lock(&xdp->atom_muxs[thread_idx]);
		printf("DONE ===>%d\n", thread_idx+1);
		idx++;
	}
	
}

inline static int	_workers_status(t_external_data *xdp)
{
	int			job_idx;
	t_thrinfo	*ti;

	job_idx = 0;
	while (job_idx < xdp->jobsnum)
	{
		ti = &xdp->tinfos[job_idx];
		if (xdp->workers == 0)
			return (DEATH);
		else if (xdp->f_death == false && should_die(ti))
		{
			xdp->workers--;
			xdp->f_death = true;
			printf("%ld %d Died\n", get_ms() - ti->ms_start, ti->id);
			return (DEATH);
		}
		job_idx++;
	}
	return (ALIVE);
}

void	schedule(t_external_data *xdp)
{
	int				worker_idx;
	int				max_workers;

	worker_idx = 0;
	max_workers= xdp->jobsnum / 2;
	while (!xdp->f_death)
	{
		_launch_workers(worker_idx, max_workers, xdp);
		worker_idx = (worker_idx + max_workers) % xdp->jobsnum;
		if (_workers_status(xdp) == DEATH)
			break ;
	}
}
