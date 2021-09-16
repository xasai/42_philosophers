#include "philo.h"

static int	_validate_args(int ac, char **av)
{
	size_t		idx;
	const char	*invalid_arg = "Arguments may contain only positive numbers";
	const char	*usage = "USAGE: ./philo  NLWP  TIMEOUT"
				 		 "WORK_TIME  SLEEP_TIME  [ITERATIONS]";

	if (ac > 6 || ac < 5)
		return (error(usage));
	while (--ac)
	{
		idx = 0;
		while (av[ac][idx])
			if (!_isdigit(av[ac][idx++]))
				return (error(invalid_arg));
	}
	return (SUCCESS);
}

static void	_clear(t_external_data *xdp)
{
	long	idx;

	idx = 0;
	printf("exiting ...\n");
	usleep(5000);
	while (idx < xdp->threads_num)
	{
		pthread_mutex_destroy(&xdp->atom_muxs[idx]);
		pthread_mutex_destroy(&xdp->unatom_muxs[idx]);
		idx++;
	}
	pthread_mutex_destroy(&xdp->w_mutex);
	free(xdp->seq);
	free(xdp->tinfos);
	free(xdp->threads);
	free(xdp->atom_muxs);
	free(xdp->unatom_muxs);
}

static int	_run(t_external_data *xdp)
{
	int			idx;
	int			thread_idx;

	idx = 0;
	while (idx < xdp->threads_num)
	{
		thread_idx = xdp->seq[idx];
		if (pthread_create(&xdp->threads[thread_idx], NULL,
				thread_entrypoint, &xdp->tinfos[idx]))
			return (error("Error: pthread_create failure"));
		if (pthread_detach(xdp->threads[thread_idx]))
			return (error("Error: pthread_detach failure"));
		idx++;
	}
	if (pthread_create(&xdp->threads[xdp->threads_num], NULL, schedule, xdp))
		return (error("pthread_create() failure"));
	if (pthread_detach(xdp->threads[xdp->threads_num]))
		return (error("Error: pthread_detach failure"));
	while (true)
	{
		if (xdp->f_death == true || xdp->threads_done == xdp->threads_num)
			break ;
		usleep(5000);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_external_data	xd;
	int				status_code;

	if (_validate_args(ac, av))
		return (EXIT_FAILURE);
	if (init(&xd, av))
	{
		_clear(&xd);
		return (EXIT_FAILURE);
	}
	debug_info(&xd);
	status_code = _run(&xd);
	_clear(&xd);
	return (status_code);
}
