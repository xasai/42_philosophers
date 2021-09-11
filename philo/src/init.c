#include "philo.h"

inline static void	_init_queue(t_external_data *xdp)
{
	int		*seq;
	int		seq_idx;	
	int		job_idx;

	job_idx = 0;
	seq_idx = 0;
	seq = xdp->seq;
	while (job_idx < xdp->jobsnum)
	{
		seq[seq_idx++] = job_idx;
		job_idx += 2;
	}
	job_idx = 1;
	while (job_idx < xdp->jobsnum)
	{
		seq[seq_idx++] = job_idx;
		job_idx += 2;
	}
}

inline static int	_init_thread_data(t_external_data *xdp, long idx)
{
	t_thrinfo	*ti;

	ti = &xdp->tinfos[idx];
	ti->xdp = xdp;
	ti->id = idx + 1;
	ti->atomic_mutex = &xdp->atom_muxs[idx];
	ti->unatomic_mutex1 = &xdp->unatom_muxs[idx];
	if (idx == 0)
		ti->unatomic_mutex2 = &xdp->unatom_muxs[xdp->jobsnum - 1];
	else
		ti->unatomic_mutex2 = &xdp->unatom_muxs[idx - 1];
	if (pthread_mutex_init(ti->atomic_mutex, NULL)
		|| pthread_mutex_init(ti->unatomic_mutex1, NULL))
	{
		return (error("pthread_mutex_init() failure"));
	}
	pthread_mutex_lock(ti->atomic_mutex);
	ti->w_mutex = &xdp->w_mutex;
	return (SUCCESS);
}

inline static int	_init_external_data(t_external_data *xdp, char **av)
{
	*xdp = (t_external_data){0};
	xdp->jobsnum = _atol(av[1]);
	if (xdp->jobsnum == 0)
		return (error("First argument should be positive not zero num."));
	xdp->tt_die = _atol(av[2]);
	xdp->tt_eat = _atol(av[3]);
	xdp->tt_sleep = _atol(av[4]);
	if (av[5])
		xdp->max_iter = _atol(av[5]);
	else
		xdp->max_iter = -1;
	xdp->threads = xmalloc(sizeof(*xdp->threads) * xdp->jobsnum + 1);
	xdp->tinfos = xmalloc(sizeof(*xdp->tinfos) * xdp->jobsnum);
	xdp->atom_muxs = xmalloc(sizeof(*xdp->atom_muxs) * xdp->jobsnum);
	xdp->unatom_muxs = xmalloc(sizeof(*xdp->unatom_muxs) * xdp->jobsnum);
	pthread_mutex_init(&xdp->w_mutex, NULL);
	xdp->seq = xmalloc(sizeof(*xdp->seq) * xdp->jobsnum);
	return (SUCCESS);
}

//TODO failure
int	init(t_external_data *xdp, char **av)
{
	long	idx;

	idx = 0;
	_init_external_data(xdp, av);
	_init_queue(xdp);
	while (idx < xdp->jobsnum)
		_init_thread_data(xdp, idx++);
	return (SUCCESS);
}
