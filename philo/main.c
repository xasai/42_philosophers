#include "philo.h" 

static int	_handle_args(int ac, char **av)
{
	const char	*usage = "./philo number_of_philosophers time_to_die time_to_eat "
					"time_to_sleep [number_of_times_each_philosopher_must_eat]";

	if (0 &&( ac > 6 || ac < 5))
		exit_error(usage);
	(void)usage;
	(void)av;
	return (RETURN_SUCCESS);
}

int	main(int ac, char **av)
{
	_handle_args(ac, av);
	dinner(av);	
	return (EXIT_SUCCESS);
}
