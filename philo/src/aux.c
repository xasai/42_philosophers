#include "philo.h"
#include <unistd.h>

int	error(const char *err)
{
	write(STDERR_FILENO, err, _strlen(err));
	write(STDERR_FILENO, "\n", 1);
	return (FAILURE);
}

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (NULL == p)
	{
		error("Error: Memory allocation failure");
		return (NULL);
	}
	return (memset(p, 0, size));
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
