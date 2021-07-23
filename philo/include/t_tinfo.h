#ifndef T_INFO_H
# define T_INFO_H

#include "t_args.h"
#include <sys/types.h>

/*
** This is argument to pthread_create function.
*/
typedef struct s_tinfo
{	
	long			id;
	t_args			*args;
	bool			*f_death;
	long			*iter_completed;
	long			ms_start;
	long			ms_last_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*l_mutex;
}				t_tinfo;

#endif	/* T_INFO_H */
