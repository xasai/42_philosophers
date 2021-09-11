#ifndef T_THRINFO_H
# define T_THRINFO_H

# include <sys/types.h>
# include <stdbool.h>

typedef struct s_thrinfo
{	
	int						id;
	long					ms_start;
	long					ms_last_eat;
	pthread_mutex_t			*atomic_mutex;
	pthread_mutex_t			*unatomic_mutex1;
	pthread_mutex_t			*unatomic_mutex2;
	pthread_mutex_t			*w_mutex;
	struct s_external_data	*xdp;
}					t_thrinfo;

#endif
