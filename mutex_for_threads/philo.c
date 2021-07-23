#include "philo_in_threads.h"

int	read_args(int ac, char **av, t_philo *philo)
{
	if (ac < 5 || ac > 6)
		return (fail("Numbers of arguments", 1));
	philo->number_of_philos = (unsigned int)ft_atoi_llu(av[1]);
	philo->time_to_die = (unsigned int)ft_atoi_llu(av[2]);
	philo->time_to_eat = (unsigned int)ft_atoi_llu(av[3]);
	philo->time_to_sleep = (unsigned int)ft_atoi_llu(av[4]);
	if (!philo->number_of_philos || !philo->time_to_die || !philo->time_to_eat
		|| !philo->time_to_sleep)
		return (fail("Wrong argument", 1));
	if (ac == 6)
	{
		philo->times_must_eat = (unsigned int)ft_atoi_llu(av[5]);
		if (!philo->times_must_eat)
			return (fail("Wrong argument", 1));
	}
	else
		philo->times_must_eat = 0;
	return (0);
}

int	mutex_init(t_philo *philo)
{
	unsigned int	i;

	philo->forks = NULL;
	philo->forks = (t_mutex *)malloc(sizeof(t_mutex) * philo->number_of_philos);
	if (!philo->forks)
		return (1);
	memset(philo->forks, 0, sizeof(t_mutex) * philo->number_of_philos);
	i = 0;
	while (i < philo->number_of_philos)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
			return (cleaner(philo, 1));
		i++;
	}
	if (pthread_mutex_init(&philo->print, NULL) != 0
		|| pthread_mutex_init(&philo->lock_forks, NULL) != 0
		|| pthread_mutex_init(&philo->dead, NULL) != 0)
		return (cleaner(philo, 1));
	pthread_mutex_lock(&philo->dead);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			philo;
	unsigned int	i;

	if (read_args(ac, av, &philo))
		return (1);
	philo.threads = NULL;
	if (mutex_init(&philo))
		return (fail("Mutex flags not allocated", 1));
	i = 0;
	while (i < philo.number_of_philos)
	{
		if (thread_add_back(&philo, new_thread(&philo)))
			return (fail("Thread data not allocated", 1));
		i++;
	}
	if (threads_start(&philo, 0) || start_control(&philo))
		return (fail("Thread don't created", 1));
	pthread_mutex_lock(&philo.dead);
	pthread_mutex_unlock(&philo.dead);
	return (cleaner(&philo, 0));
}
