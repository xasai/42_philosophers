#ifndef T_CONFIG_H
# define T_CONFIG_H

# include "t_args.h"
# include "t_tinfo.h"
# include <stdint.h>

/*
** Main process info.
*/

typedef struct s_config
{
	t_args			args;
	long			iter_max;
	long			iter_completed;
	bool			f_death;
	t_tinfo			*tinfo;
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;
}					t_config;

#endif /* T_CONFIG_H */
