#ifndef T_EXTERNAL_DATA_H
# define T_EXTERNAL_DATA_H

# include <stdbool.h>
# include <sys/types.h>

# define MAX_PARAMS 5
//=====================
# define TNUM		0
# define DIE		1 
# define EAT		2 
# define SLEEP		3 
# define MAX_ITER	4

typedef struct s_external_data
{
	int  				jobsnum;
	int  				tt_die;
	int  				tt_eat;
	int  				tt_sleep;
	int  				max_iter;
	bool				f_death;
	int					workers;
	int					*seq;
	struct s_thrinfo	*tinfos;
	pthread_t			*threads;
	pthread_mutex_t		*atom_muxs;
	pthread_mutex_t		*unatom_muxs;
}					t_external_data;

#endif /* T_EXTERNAL_DATA_H */
