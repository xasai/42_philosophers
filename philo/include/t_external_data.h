#ifndef T_EXTERNAL_DATA_H
# define T_EXTERNAL_DATA_H

# include <stdbool.h>
# include <sys/types.h>

typedef struct s_external_data
{
	int					jobsnum;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					max_iter;
	int					threads_done;	
	bool				f_death;
	int					*seq;
	struct s_thrinfo	*tinfos;
	pthread_t			*threads;
	pthread_mutex_t		*atom_muxs;
	pthread_mutex_t		*unatom_muxs;
	pthread_mutex_t		w_mutex;
}					t_external_data;

//T_EXTERNAL_DATA_H
#endif
