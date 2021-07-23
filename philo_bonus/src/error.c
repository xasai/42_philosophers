#include "philo.h"

void exit_error(const char *message)
{
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	exit (EXIT_FAILURE);
}
