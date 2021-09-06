#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# include <pthread.h>

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
void		schedule(t_external_data *xdp);
bool		should_die(t_thrinfo *inf);

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
