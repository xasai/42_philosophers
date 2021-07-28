#ifndef T_EXTERNAL_DATA_H
# define T_EXTERNAL_DATA_H

# include "t_thrinfo.h"
# include <stdint.h>
# define P_ARG_MAX 5

typedef struct s_config
{
	int64_t		tnum;
	int64_t		tt_die;
	int64_t		tt_eat;
	int64_t		tt_sleep;
	int64_t		iter_max;
	int64_t		iter_completed;
	bool			f_death;
	t_tinfo			*tinfo;
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;
}					t_config;

typedef struct s_external_data
{
	long			argv[P_ARG_MAX]
	bool			f_death;
	int				iter_completed;
	pthread_t		*threads;
	pthread_mutex_t	*atomic_mutexes;
	pthread_mutex_t	*unatomic_mutexes;
	t_thrinfo		*thrinfos;
}					t_external_data;

#endif /* T_EXTERNAL_DATA_H */
