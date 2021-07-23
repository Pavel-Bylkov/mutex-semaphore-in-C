#include "philo_in_proc.h"

int	read_args(int ac, char **av, t_main *main)
{
	if (ac < 5 || ac > 6)
		return (fail("Numbers of arguments", 1));
	main->number_of_philos = (unsigned int)ft_atoi_llu(av[1]);
	main->time_to_die = (unsigned int)ft_atoi_llu(av[2]);
	main->time_to_eat = (unsigned int)ft_atoi_llu(av[3]);
	main->time_to_sleep = (unsigned int)ft_atoi_llu(av[4]);
	if (!main->number_of_philos || !main->time_to_die || !main->time_to_eat
		|| !main->time_to_sleep || main->number_of_philos > 200
		|| main->time_to_die < 60 || main->time_to_eat < 60
		|| main->time_to_sleep < 60)
		return (fail("Wrong argument", 1));
	if (ac == 6)
	{
		main->times_must_eat = (unsigned int)ft_atoi_llu(av[5]);
		if (!main->times_must_eat)
			return (fail("Wrong argument", 1));
	}
	else
		main->times_must_eat = 0;
	main->philos = (t_proc *)malloc(sizeof(t_proc) * main->number_of_philos);
	if (!main->philos)
		return (fail("Process data not allocated", 1));
	return (0);
}

int	start_process(t_proc *philo, t_main *main)
{
	int					r;

	r = pthread_create(&philo->control_die, NULL, controller_die,
			(void *)philo);
	if (r || pthread_detach(philo->control_die))
		return (1);
	while (1)
	{
		philo_eating(philo, main->tstmp_start);
		philo_sleeping(philo, main->tstmp_start);
		print_msg(philo->main->print, get_timestamp() - main->tstmp_start,
			philo->nbr, " is thinking");
		sem_post(philo->main->print);
	}
	return (0);
}

int	start_group_proc(t_main *main, unsigned int f, unsigned long long time_dead)
{
	unsigned int	i;

	i = 0;
	while (i < main->number_of_philos)
	{
		if ((i + 1) % 2 == f)
		{
			main->philos[i].tstmp_die = time_dead;
			if (init_philos(&main->philos[i], i, main))
				return (1);
			main->philos[i].pid = fork();
			if (main->philos[i].pid < 0)
				return (1);
			else if (main->philos[i].pid == 0)
				exit(start_process(&main->philos[i], main));
		}
		usleep(50);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_main				main;
	unsigned long long	time_dead;

	if (read_args(ac, av, &main) || init_sema(&main))
		return (1);
	main.tstmp_start = get_timestamp();
	time_dead = main.tstmp_start + main.time_to_die;
	if (start_group_proc(&main, 0, time_dead)
		|| start_group_proc(&main, 1, time_dead))
		return (fail("Fork error", cleaner(&main, 1)));
	if (start_control(&main))
		return (fail("Thread controller not start", cleaner(&main, 1)));
	sem_wait(main.dead);
	return (cleaner(&main, 0));
}
