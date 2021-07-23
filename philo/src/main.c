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

static void	run(t_config *cfg)
{
	long			tnum;
	short int		launch;
	t_tinfo			*tinfo;
	pthread_t		*threads;

	launch = 0;
	tinfo =	cfg->tinfo;
	threads = cfg->threads;
	while (launch < 2)
	{
		tnum = launch;
		while (tnum < cfg->args.tnum)
		{
			tinfo[tnum].ms_start = get_ms();
			if (pthread_create(&threads[tnum], NULL, lifecycle_start, &tinfo[tnum]))
				exit_error("pthread_create(): Failure allocating thread");
			pthread_detach(threads[tnum]);
			tnum += 2;
		}
		launch++;
	}
	start_monitoring(cfg);
}

int	main(int ac, char **av)
{
	t_config	cfg;

	_handle_args(ac, av);
	cfg = configuration_init(av);
	tinfo_init(&cfg);
	run(&cfg);
	return (EXIT_SUCCESS);
}
