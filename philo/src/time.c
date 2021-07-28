#include "philo.h"

inline uint64_t	ms(struct timeval *from)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - from->tv_sec) * 1000\
			 + (now.tv_usec - from->tv_usec) / 1000);
}

inline long get_usec()
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec) * (long int)1000000 + now.tv_usec);
}

inline long to_usec(struct timeval *t)
{
	return ((t->tv_sec) * (long int)1000000 + t->tv_usec);
}

inline long get_ms()
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec) * (long int)1000 + (now.tv_usec) / 1000);

}
inline long to_ms(struct timeval *t)
{
	return ((t->tv_sec) * (long int)1000 + (t->tv_usec) / 1000);
}

bool	msleep(int tt_sleep, t_tinfo *tinfo) // 1 ms погрешность ??
{
	long start;
	long end;

	start = get_ms();
	end = start + tt_sleep;
	while (start < end)
	{
		start = get_ms();
		if (should_die(tinfo))
			return (RETURN_FAILURE);
		usleep(200);
	}
	return (RETURN_SUCCESS);
}
