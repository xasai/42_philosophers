#include "philo.h" 

static int _handle_args(int ac, char **av)
{
	if (ac > 6 || ac < 5)
		return (RETURN_FAILURE);
	(void)av;
	return (RETURN_SUCCESS);
}

int main(int ac, char **av)
{
	_handle_args(ac, av);
	exit(EXIT_SUCCESS);
}
