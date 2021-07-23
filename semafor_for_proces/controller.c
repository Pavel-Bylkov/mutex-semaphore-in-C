#include "philo_in_proc.h"

int	start_control(t_main *main)
{
	int	r;

	if (main->times_must_eat > 0)
	{
		r = pthread_create(&main->control_eat, NULL,
				controller_eat, (void *)main);
		if (r || pthread_detach(main->control_eat))
			return (cleaner(main, r));
	}
	return (0);
}

void	*controller_eat(void *arg)
{
	t_main			*main;
	unsigned int	i;

	main = (t_main *)arg;
	i = 0;
	while (i < main->number_of_philos)
		sem_wait(main->end_eat[i++]);
	i = 0;
	while (i < main->number_of_philos)
		kill(main->philos[i++].pid, SIGKILL);
	sem_post(main->dead);
	return (NULL);
}

void	*controller_die(void *arg)
{
	t_proc				*man;
	unsigned long long	timer;

	man = (t_proc *)arg;
	while (1)
	{
		sem_wait(man->lock_eat);
		timer = get_timestamp();
		if (timer > man->tstmp_die)
		{
			print_msg(man->main->print, timer - man->main->tstmp_start,
				man->nbr, " died");
			sem_post(man->main->dead);
			return (NULL);
		}
		sem_post(man->lock_eat);
		usleep(1000);
	}
	return (NULL);
}
