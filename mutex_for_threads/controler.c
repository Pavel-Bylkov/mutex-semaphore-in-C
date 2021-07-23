#include "philo_in_threads.h"

int	start_control(t_philo *philo)
{
	int	r;

	if (philo->times_must_eat > 0)
	{
		r = pthread_create(&philo->control_eat, NULL, controller_eat,
				(void *)philo);
		if (r || pthread_detach(philo->control_eat))
			return (cleaner(philo, r));
	}
	return (0);
}

static unsigned int	check_flags(int *flags, t_philo *philo)
{
	unsigned int	sum;
	t_lst_threads	*tmp;

	tmp = philo->threads;
	sum = 0;
	while (tmp)
	{
		if (!flags[tmp->nbr - 1] && tmp->times_eat == philo->times_must_eat)
			flags[tmp->nbr - 1] = 1;
		sum += flags[tmp->nbr - 1];
		tmp = tmp->next;
	}
	return (sum);
}

void	*controller_eat(void *arg)
{
	t_philo				*philo;
	int					*flags;

	philo = (t_philo *)arg;
	flags = (int *)malloc(sizeof(int) * philo->number_of_philos);
	memset(flags, 0, sizeof(int) * (size_t)philo->number_of_philos);
	while (1)
	{
		if (check_flags(flags, philo) == philo->number_of_philos)
		{
			free(flags);
			pthread_mutex_unlock(&philo->dead);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
