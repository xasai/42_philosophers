#include "philo.h" 
#include "t_external_data.h"
#ifdef _DEBUG
# include <signal.h>
# include <stdio.h>
# include <execinfo.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

void	_segv_handler(int sig)
{
	void		*array[10];
	size_t		size;

	size = backtrace(array, 10);
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

void	debug_info(t_external_data *xdp)
{
	int	idx;

	idx = 0;
	signal(SIGSEGV, _segv_handler);
	printf(" Queue: ");
	while (idx < xdp->jobsnum - 1)
		printf("%d, ", xdp->seq[idx++] + 1);
	printf("%d\n", xdp->seq[idx]);
	idx = 0;
	printf(" Forks: \n");
	while (idx < xdp->jobsnum)
	{
		printf(" [%d] %p %p\n", idx + 1,
			(void *)xdp->tinfos[idx].unatomic_mutex1,
			(void *)xdp->tinfos[idx].unatomic_mutex1);
		idx++;
	}
	printf("----------------------------------\n\n");
}

/* _DEBUG */
#else

void	debug_info(t_external_data *x)
{
	(void)x;
}

#endif
