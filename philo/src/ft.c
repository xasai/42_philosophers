#include "philo.h"

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

uint64_t _atoi64(const char *nptr)
{
	uint64_t	num;

	num = 0;
	while (_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (num);
}
