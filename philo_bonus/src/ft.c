#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (NULL == p)
		exit_error("Memory allocation failure");
	return (memset(p, 0, size));
}

bool ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *nptr)
{
	long	num;
	int		sign;

	sign = 1;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 7 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*(nptr++) == '-')
			sign = -1;
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * (int)num);
}
