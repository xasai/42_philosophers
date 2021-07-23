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

long	_atol(const char *nptr)
{
	long	num;
	short	sign;

	num = 0;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (num * sign);
}
