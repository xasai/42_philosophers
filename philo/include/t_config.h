#ifndef T_CONFIG_H
# define T_CONFIG_H

# include "t_tinfo.h"
# include <stdint.h>

/*
** Main process info.
*/

typedef struct s_config
{
	uint64_t		tnum;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep;
	int64_t			iter_max;
	uint64_t		iter_completed;
	bool			f_death;
	t_tinfo			*tinfo;
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;
}					t_config;

#endif /* T_CONFIG_H */
