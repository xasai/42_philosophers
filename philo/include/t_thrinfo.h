#ifndef T_THRINFO_H
# define T_THRINFO_H

//FIXME
#include <sys/types.h>
#include <sys/time.h>
#include <stdint.h>
//#include "t_external_data.h" 

typedef struct s_tinfo
{	
	int64_t		id;
	int64_t		tt_die;
	int64_t		tt_eat;
	int64_t		tt_sleep;
	int64_t			iter_max;
	int64_t		*iter_completed;
	bool			*f_death;
	struct timeval	tv_start;
	struct timeval	tv_last_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*l_mutex;
}				t_tinfo;

typedef struct s_thrinfo
{	
	int				id;
	long			ms_start;
	long			ms_last_eat;
	pthread_mutex_t *atomic_mutex;
	pthread_mutex_t	*unatomic_mutex1;
	pthread_mutex_t	*unatomic_mutex2;
	//t_external_data *ex;
}					t_thrinfo;


#endif	/* T_THRINFO_H */
