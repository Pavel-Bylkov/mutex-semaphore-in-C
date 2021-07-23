#include "philo_in_proc.h"

int	init_endeat(t_main *main, int flag)
{
	int		i;
	char	*index;
	t_proc	*tmp;

	i = 0;
	while (i < (int)main->number_of_philos)
	{
		index = ft_itoa(i);
		tmp = &main->philos[i];
		tmp->s_name_end = ft_strjoin(S_ENDEAT, index);
		free(index);
		sem_unlink(tmp->s_name_end);
		main->end_eat[i] = sem_open(tmp->s_name_end, flag, 0644, 0);
		if (main->end_eat[i++] == SEM_FAILED)
			return (1);
	}
	return (0);
}

int	init_sema(t_main *main)
{
	int		flag;

	flag = O_CREAT | O_EXCL;
	sem_unlink(S_FORK);
	sem_unlink(S_PRINT);
	sem_unlink(S_DEAD);
	main->forks = sem_open(S_FORK, flag, 0644,
			main->number_of_philos);
	main->print = sem_open(S_PRINT, flag, 0644, 1);
	main->dead = sem_open(S_DEAD, flag, 0644, 0);
	if (main->forks == SEM_FAILED || main->print == SEM_FAILED
		|| main->dead == SEM_FAILED)
		return (1);
	main->end_eat = (sem_t **)malloc(sizeof(sem_t *)
			* main->number_of_philos);
	if (!main->end_eat)
		return (fail("Sem array not allocated", 1));
	return (init_endeat(main, flag));
}

int	init_philos(t_proc *philo, int i, t_main *main)
{
	char	*index;

	philo->nbr = i + 1;
	philo->times_eat = 0;
	philo->main = main;
	index = ft_itoa(i);
	philo->s_name = ft_strjoin(S_EAT, index);
	sem_unlink(philo->s_name);
	philo->lock_eat = sem_open(philo->s_name,
			O_CREAT | O_EXCL, 0644, 1);
	if (philo->lock_eat == SEM_FAILED)
		return (1);
	free(index);
	return (0);
}
