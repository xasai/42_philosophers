#include "philo.h"

static int	_handle_args(int ac, char **av)
{
	size_t		idx;
	const char	*invalid_arg = "Arguments may contain only positive numbers";
	const char	*usage = "./philo {philo_count} {time_to_die} {time_to_eat}"
							" {time_to_sleep} [number_of_iterations]";

	if (ac > 6 || ac < 5)
		exit_error(usage);
	while (--ac)
	{
		idx = 0;
		while (av[ac][idx])
			if (!_isdigit(av[ac][idx++]))
				exit_error(invalid_arg);
	}
	return (RETURN_SUCCESS);
}

inline static void	_clear(t_external_data *xdp)
{
	long	idx;

	usleep(20000);
	idx = 0;
	while (idx < xdp->argv[TNUM])
	{
		pthread_mutex_destroy(&xdp->atomic_mutexes[idx]);
		pthread_mutex_destroy(&xdp->unatomic_mutexes[idx]);
		idx++;
	}
	free(xdp->thr_infos);
	free(xdp->atomic_mutexes);
	free(xdp->unatomic_mutexes);
}

inline static void	_run(t_external_data *xdp)
{
	long		idx;
	pthread_t	sched;

	idx = 0;
	while (idx < xdp->argv[TNUM])
	{
		if (pthread_create(&xdp->threads[idx], NULL,
				thread_entrypoint, &xdp->thr_infos[idx]))
		{
			exit_error("pthread_create() failure");
		}
		pthread_detach(xdp->threads[idx]);
		idx++;
	}
	if (pthread_create(&sched, NULL, sched_entrypoint, xdp))
		exit_error("pthread_create() failure");
	pthread_join(sched, NULL);
	_clear(xdp);
}

int	main(int ac, char **av)
{
	t_external_data	xd;

	_handle_args(ac, av);
	init(&xd, av);
	_run(&xd);
	exit(RETURN_SUCCESS);
}
