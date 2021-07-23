#ifndef PHILO_H
# define PHILO_H

						/*	Allowed functions	*/

# include <stdio.h>		/*	printf				*/
# include <stdlib.h>	/*	malloc, free		*/
# include <unistd.h>	/*	write, usleep		*/
# include <string.h>	/*	memset				*/
# include <sys/time.h>	/*	gettimeofday		*/

# include <pthread.h>	/*	pthread_create	
							pthread_detach
							pthread_join
							pthread_mutex_init
							pthread_mutex_destroy
							pthread_mutex_lock
							pthread_mutex_unlock
						*/

#include <stdbool.h>

# include "t_state.h"
# include "t_philo.h"

# define RETURN_FAILURE EXIT_FAILURE
# define RETURN_SUCCESS EXIT_SUCCESS

int		error(const char *message);
void	exit_error(const char *message);

/*		ft.c					*/
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
bool	ft_isdigit(char c);
void	*xmalloc(size_t size);

#endif
