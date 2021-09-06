#include "philo.h"

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (NULL == p)
		exit_error("Memory allocation failure");
	return (memset(p, 0, size));
}

void	exit_error(const char *message)
{
	if (message)
		write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);
	exit (EXIT_FAILURE);
}

size_t	_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long	_atol(const char *nptr)
{
	long	num;

	num = 0;
	while (_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (num);
}
