#include "philo.h"

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (NULL == p)
		exit_error("Memory allocation failure");
	return (memset(p, 0, size));
}

void exit_error(const char *message)
{
	if (message)
		write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);
	exit (EXIT_FAILURE);
}

