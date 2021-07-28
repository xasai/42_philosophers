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

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

# include "t_thrinfo.h"
# include "t_external_data.h"

# define EXIT_SUCCESS 0 
# define EXIT_FAILURE 1 
# define RETURN_SUCCESS EXIT_SUCCESS
# define RETURN_FAILURE EXIT_FAILURE

/*		Args indexes	*/
# define TNUM		0
# define DIE		1 
# define EAT		2 
# define SLEEP		3 
# define MAX_ITER	4


/*		init.c						*/
void		tinfo_init(t_config *cfg);
void		thrinfo_init(t_config *cfg);
t_config	configuration_init(char **av);

/*		monitor.c					*/
void		start_monitoring(t_config *cfg);
bool		should_die(t_thrinfo *tinfo); //TODO inline 

/*		lifecycle.c					*/
void		*lifecycle_start(void *arg);

/*		aux.c						*/
void		*xmalloc(size_t size);
void		exit_error(const char *message);
//uint64_t	ms(struct timeval *from);
bool		msleep(int tt_sleep, t_tinfo *tinfo);

long		get_ms();
long		to_ms(struct timeval *t);
long		get_usec();
long		to_usec(struct timeval *t);

/*		ft.c						*/
uint64_t	_atoi64(const char *nptr);
//long		_atol(const char *nptr); // TODO
size_t		_strlen(const char *s);
bool		_isdigit(char c);

#endif
