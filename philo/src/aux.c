#include "philo.h"

inline uint64_t	ms(struct timeval *from)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - from->tv_sec) * 1000\
			 + (now.tv_usec - from->tv_usec) / 1000);
}

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (NULL == p)
		exit_error("Memory allocation failure");
	return (memset(p, 0, size));
}

long get_ms()
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec) * (long int)1000 + (now.tv_usec) / 1000);


}

bool	msleep(int tt_sleep, t_tinfo *tinfo) // 1 ms погрешность
{
	long start = get_ms();
	long offset = 0;
	
	while (offset < tt_sleep)
	{
		offset = get_ms() - start;
		if (should_die(tinfo))
			return (RETURN_FAILURE);
		usleep(70);
	}
	return (RETURN_SUCCESS);
}
/*
bool	msleep(int tt_sleep, t_tinfo *tinfo) // 1 ms погрешность
{
	struct timeval	now;
	int64_t			end;

	gettimeofday(&now, NULL);
	end = (now.tv_sec * 1000) + (now.tv_usec / 1000) + tt_sleep;
	while (!*tinfo->f_death)
	{
		gettimeofday(&now, NULL);
		if (end <= (now.tv_sec * 1000) + (now.tv_usec / 1000))
			break ;
		if (should_die(tinfo))
			return (RETURN_FAILURE);
		usleep(70);
	}
	return (RETURN_SUCCESS);
}*/

void exit_error(const char *message)
{
	if (message)
		write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);
	exit (EXIT_FAILURE);
}
