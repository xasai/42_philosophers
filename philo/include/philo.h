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

# include <sys/types.h>
# include <stdint.h>
# include <stdbool.h>

# include "t_thrinfo.h"
# include "t_external_data.h"

# define EXIT_SUCCESS 0 
# define EXIT_FAILURE 1 
# define RETURN_SUCCESS EXIT_SUCCESS
# define RETURN_FAILURE EXIT_FAILURE

//init.c
void		init(t_external_data *xdp, char **av);

//lifecycle.c
void		*thread_entrypoint(void *arg);
bool		should_die(t_thrinfo *ti);

//sched.c
void		*sched_entrypoint(void *arg);

//time.c
long		get_ms(void);
bool		msleep(long ms_duration, t_thrinfo *ti);

//aux.c
void		*xmalloc(size_t size);
void		exit_error(const char *message);

//ft.c
size_t		_strlen(const char *s);
long		_atol(const char *nptr);
bool		_isdigit(char c);

#endif
