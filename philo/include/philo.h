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
# define SUCCESS EXIT_SUCCESS
# define FAILURE EXIT_FAILURE

//init.c
//init initializes xdp, create threads + thrinfos and fill its fields with argv
int			init(t_external_data *xdp, char **av);

//lifecycle.c
//thread_entrypoint 'philo' entrypoint
void		*thread_entrypoint(void *arg);

//sched.c
//schedule  officiant, run in separate thread
void		*schedule(void *xdp);

//sched.c
//should_die returns true if thread didn't eat more than tt_die msec
bool		should_die(t_thrinfo *inf);

//time.c
//get_ms returns current time of day in milliseconds
long		get_ms(void);

//time.c
//same as usleep but calls inside should_die function
//returns true if thread should interrupt
bool		msleep(long ms_duration, t_thrinfo *ti);

//aux.c
//xmalloc doesnt exits but printing corresponding
//message if malloc inside it failed
void		*xmalloc(size_t size);

//aux.c
//error prints error to STERR_FILENO and returns FAILURE status
int			error(const char *err);

//ft.c 
//std functions
size_t		_strlen(const char *s);
long		_atol(const char *nptr);
bool		_isdigit(char c);

//debug.c
void		debug_info(t_external_data *xd);

#endif
