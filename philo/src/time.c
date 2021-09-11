#include "philo.h"

inline long	get_ms(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec) * (long int)1000 + (now.tv_usec) / 1000);
}

inline bool	msleep(long ms_duration, t_thrinfo *ti)
{
	long	start;
	long	end;

	start = get_ms();
	end = start + ms_duration;
	while (start < end)
	{
		start = get_ms();
		if (should_die(ti))
			return (RETURN_FAILURE);
		usleep(100);
	}
	return (RETURN_SUCCESS);
}
