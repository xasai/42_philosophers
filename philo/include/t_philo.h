#ifndef T_PHILO
# define T_PHILO

# include <pthread.h>

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
}				t_philo;

# endif /*	T_PHILO	*/
