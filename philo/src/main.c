#include "philo.h"

#ifdef _DEBUG
# include <signal.h>
# include <stdio.h>
# include <execinfo.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

void _segv_handler(int sig)
{
  void *array[10];
  size_t size;

  size = backtrace(array, 10);

  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}
/* _DEBUG */
#endif 


static int	_handle_args(int ac, char **av)
{
	size_t		idx;
	const char	*invalid_arg = "Arguments may contain only positive numbers";
	const char	*usage = "./philo {philo_count} {time_to_die} {time_to_eat}"
							" {time_to_sleep} [number_of_iterations]";

	if (ac > 6 || ac < 5)
		exit_error(usage);
	while (--ac)
	{
		idx = 0;
		while (av[ac][idx])
			if (!_isdigit(av[ac][idx++]))
				exit_error(invalid_arg);
	}
	return (RETURN_SUCCESS);
}

static void	_xdp_clear(t_external_data *xdp)
{
	long	idx;

	idx = 0;
	while (idx < xdp->jobsnum)
	{
		pthread_mutex_destroy(&xdp->atom_muxs[idx]);
		pthread_mutex_destroy(&xdp->unatom_muxs[idx]);
		idx++;
	}
	free(xdp->seq);
	free(xdp->tinfos);
	free(xdp->threads);
	free(xdp->atom_muxs);
	free(xdp->unatom_muxs);
}

static void	_run(t_external_data *xdp)
{
	int			idx;
	int			err;
	int  		thread_idx;

	idx = 0;
	while (idx < xdp->jobsnum)
	{
		thread_idx = xdp->seq[idx];
		err = pthread_create(&xdp->threads[thread_idx], NULL,
				thread_entrypoint, &xdp->tinfos[idx]);
		if (err)
			exit_error("pthread_create() failure");
		pthread_detach(xdp->threads[idx]);
		idx++;
	}
	schedule(xdp);
	_xdp_clear(xdp);
}

void debug_info(t_external_data *xdp)
{
	int idx;
	
	idx = 0;
	printf(" Queue: ");
	while (idx < xdp->jobsnum - 1)
	{
		printf("%d, ", xdp->seq[idx++]);
	}
	printf("%d\n", xdp->seq[idx]);
	idx = 0;
	printf(" Forks: \n");
	while (idx < xdp->jobsnum - 1)
	{
		printf("[%d] %p %p\n", idx + 1, 
			(void *)xdp->tinfos[idx].unatomic_mutex1,
			(void *)xdp->tinfos[idx].unatomic_mutex1);
	}
}

int	main(int ac, char **av)
{
	t_external_data	xd;
	_handle_args(ac, av);
	init(&xd, av);
#ifdef _DEBUG
	signal(SIGSEGV, _segv_handler);
	debug_info(xd)
#endif
	_run(&xd);
	return (RETURN_SUCCESS);
}
