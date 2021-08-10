#include "philo.h"

#define _VERBOSE 1
inline static void	_run_jobs(int job_idx, int jobs_max, t_external_data *xdp)
{
	int	idx;
	int	thread_idx;

	idx = 0;
	while (idx < jobs_max)
	{
		thread_idx = xdp->seq[((job_idx + idx) % xdp->argv[TNUM])];
		pthread_mutex_unlock(&xdp->atomic_mutexes[thread_idx]);
		if (_VERBOSE)
			printf("=====================>%d\n", thread_idx + 1);
		idx++;
	}
	idx = 0;
}

inline static int	_death_watcher(t_external_data *xdp)
{
	long		thr_idx;
	t_thrinfo	*ti;

	thr_idx = 0;
	while (thr_idx < xdp->argv[TNUM])
	{
		ti = &xdp->thr_infos[thr_idx];
		if (xdp->threads_done == xdp->argv[TNUM])
			return (RETURN_FAILURE);
		else if (xdp->f_death == false && should_die(ti))
		{
			xdp->threads_done++;
			xdp->f_death = true;
			printf("%ld %d Died\n", get_ms() - ti->ms_start, ti->id);
			return (RETURN_FAILURE);
		}
		thr_idx++;
	}
	return (RETURN_SUCCESS);
}

void	*sched_entrypoint(void *arg)
{
	int				job_idx;
	int				jobs_max;
	t_external_data	*xdp;

	xdp = arg;
	job_idx = 0;
	jobs_max = xdp->argv[TNUM] / 2;
	while (!xdp->f_death)
	{
		_run_jobs(job_idx, jobs_max, xdp);
		msleep(xdp->argv[EAT], &xdp->thr_infos[0]);
		job_idx += jobs_max;
		job_idx %= xdp->argv[TNUM];
		if (_death_watcher(xdp) == RETURN_FAILURE)
			break ;
	}
	return (NULL);
}
