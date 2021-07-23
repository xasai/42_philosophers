#include "philo.h" 

static int	_handle_args(int ac, char **av)
{
	size_t		idx;
	const char	*invalid_arg= "Arguments may contain only positive numbers";
	const char	*usage = "./philo {philo_count} {time_to_die} {time_to_eat}"
							" {time_to_sleep} [number_of_iterations]";
	if (( ac > 6 || ac < 5))
		exit_error(usage);
	while (--ac)
	{
		idx = 0;
		while (av[ac][idx])
			if (!ft_isdigit(av[ac][idx++]))
				exit_error(invalid_arg);
	}
	return (RETURN_SUCCESS);
}

static t_config	*_configuration_init(int ac, char *av)
{
	i
}

int	main(int ac, char **av)
{
	t_config	*config
	_handle_args(ac, av);
	_configuration_init(ac, av);

	return (EXIT_SUCCESS);
}
