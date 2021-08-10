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
	long				argv[MAX_PARAMS];
	bool				f_death;
	int					threads_done;
	int					*seq;
	pthread_t			*threads;
	pthread_mutex_t		*atomic_mutexes;
	pthread_mutex_t		*unatomic_mutexes;
	struct s_thrinfo	*thr_infos;
}					t_external_data;

#endif /* T_EXTERNAL_DATA_H */
