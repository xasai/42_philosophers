#include "philo.h"
#include <stdio.h>

inline static void	_init_queue(t_external_data *xdp)
{
	int		*seq;
	int		seq_idx;	
	int		thr_idx;

	thr_idx = 0;
	seq_idx = 0;
	seq = xmalloc(sizeof(*seq) * xdp->argv[TNUM]);
	while (thr_idx < xdp->argv[TNUM])
	{
		seq[seq_idx++] = thr_idx;
		thr_idx += 2;
	}
	thr_idx = 1;
	while (thr_idx < xdp->argv[TNUM])
	{
		seq[seq_idx++] = thr_idx;
		thr_idx += 2;
	}
	xdp->seq = seq;
}

inline static void	_init_thread_data(t_external_data *xdp, long idx)
{
	t_thrinfo	*ti;

	ti = &xdp->thr_infos[idx];
	ti->xdp = xdp;
	ti->id = idx + 1;
	ti->atomic_mutex = &xdp->atomic_mutexes[idx];
	ti->unatomic_mutex1 = &xdp->unatomic_mutexes[idx];
	if (idx == 0)
		idx = xdp->argv[TNUM];
	ti->unatomic_mutex2 = &xdp->unatomic_mutexes[idx - 1];
	if (pthread_mutex_init(ti->atomic_mutex, NULL)
		|| pthread_mutex_init(ti->unatomic_mutex1, NULL)
		|| pthread_mutex_init(ti->unatomic_mutex2, NULL))
	{
		exit_error("pthread_mutex_init() failure");
	}
	ti->ms_start = get_ms();
	ti->ms_last_eat = ti->ms_start;
	pthread_mutex_lock(ti->atomic_mutex);
}

inline static void	_init_external_data(t_external_data *xdp, char **av)
{
	*xdp = (t_external_data){.argv[MAX_ITER] = -1};
	xdp->argv[TNUM] = _atol(av[1]);
	if (xdp->argv[TNUM] == 0)
		exit_error("First argument should be positive not zero num.");
	xdp->argv[DIE] = _atol(av[2]);
	xdp->argv[EAT] = _atol(av[3]);
	xdp->argv[SLEEP] = _atol(av[4]);
	if (av[5])
		xdp->argv[MAX_ITER] = _atol(av[5]);
	xdp->threads = xmalloc(sizeof(*xdp->threads) * xdp->argv[TNUM]);
	xdp->thr_infos = xmalloc(sizeof(*xdp->thr_infos) * xdp->argv[TNUM]);
	xdp->atomic_mutexes = xmalloc(sizeof(*xdp->atomic_mutexes)
			* xdp->argv[TNUM]);
	xdp->unatomic_mutexes = xmalloc(sizeof(*xdp->unatomic_mutexes)
			* xdp->argv[TNUM]);
}

void	init(t_external_data *xdp, char **av)
{
	long	idx;

	idx = 0;
	_init_external_data(xdp, av);
	_init_queue(xdp);
	while (idx < xdp->argv[TNUM])
		_init_thread_data(xdp, idx++);
}
