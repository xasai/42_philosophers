#ifndef T_INFO_H
# define T_INFO_H

#include <sys/types.h>
#include <sys/time.h>
#include <stdint.h>

/*
** This is argument to pthread_create function.
*/

typedef struct s_tinfo
{	
	uint64_t		id;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep;
	int64_t			iter_max;
	uint64_t		*iter_completed;
	bool			*f_death;
	struct timeval	tv_start;
	struct timeval	tv_last_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*l_mutex;
}				t_tinfo;

#endif	/* T_INFO_H */
