#include "philo.h"

static bool *forks;

static void *eat(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (true)
	{
		printf("MY Id is %d\n", philo->id);
		usleep(1000000);
	}
	return (NULL);
}

void	dinner(char **av)
{
	size_t	idx;
	size_t	philo_count;
	t_philo *philo;
	t_philo *philos;
	
	idx = 0;
	philo_count = ft_atoi(av[1]);
	philos = xmalloc(sizeof(*philos) * (philo_count - 1));
	forks = xmalloc(sizeof(*forks) * (philo_count- 1));
	while (idx <= philo_count - 1)
	{
		philo = &philos[idx];
		philo->id = idx + 1; 
		if (pthread_create(&philo->thread, NULL, eat, philo))
			exit_error("Thread allocation failure");//FIXME message
		idx++;
	}
	pthread_join(philo->thread, NULL);
}
