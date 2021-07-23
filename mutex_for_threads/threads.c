#include "philo_in_threads.h"

t_lst_threads	*new_thread(t_philo *philo)
{
	t_lst_threads	*new;

	new = (t_lst_threads *)malloc(sizeof(t_lst_threads));
	if (!new)
		return (NULL);
	new->thread = 0;
	new->control_die = 0;
	new->nbr = 0;
	new->time_to_die = philo->time_to_die;
	new->time_to_eat = philo->time_to_eat;
	new->time_to_sleep = philo->time_to_sleep;
	new->left = NULL;
	new->right = NULL;
	new->tstmp_eat = 0;
	new->tstmp_eat = 0;
	new->times_eat = 0;
	new->print = &philo->print;
	new->lock_forks = &philo->lock_forks;
	new->dead = &philo->dead;
	new->next = NULL;
	return (new);
}

int	thread_add_back(t_philo *philo, t_lst_threads *new)
{
	t_lst_threads	*last;

	if (!new || pthread_mutex_init(&new->lock_eat, NULL) != 0)
		return (cleaner(philo, 1));
	if (philo->threads == NULL)
	{
		new->nbr = 1;
		philo->threads = new;
	}
	else
	{
		last = philo->threads;
		while (last->next != NULL)
			last = last->next;
		new->nbr = last->nbr + 1;
		last->next = new;
	}
	new->left = &philo->forks[new->nbr % philo->number_of_philos];
	new->right = &philo->forks[new->nbr - 1];
	return (0);
}

int	start_odd_thread(t_philo *philo)
{
	t_lst_threads	*tmp;
	int				r;

	usleep(100);
	tmp = philo->threads;
	while (tmp)
	{
		if (tmp->nbr % 2 != 0)
		{
			r = pthread_create(&tmp->thread, NULL, life_philo, (void *)tmp);
			if (r || pthread_detach(tmp->thread))
				return (cleaner(philo, r));
		}
		usleep(50);
		tmp = tmp->next;
	}
	return (0);
}

int	threads_start(t_philo *philo, int r)
{
	t_lst_threads		*tmp;
	unsigned long long	timer;

	if (!philo->threads)
		return (1);
	tmp = philo->threads;
	timer = get_timestamp(1);
	while (tmp)
	{
		tmp->tstmp_eat = timer;
		tmp->tstmp_die = tmp->tstmp_eat + philo->time_to_die;
		if (tmp->nbr % 2 == 0)
		{
			r = pthread_create(&tmp->thread, NULL, life_philo, (void *)tmp);
			if (r || pthread_detach(tmp->thread))
				return (cleaner(philo, r));
		}
		tmp = tmp->next;
	}
	return (start_odd_thread(philo));
}
