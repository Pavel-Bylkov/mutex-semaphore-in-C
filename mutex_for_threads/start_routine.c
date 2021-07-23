#include "philo_in_threads.h"

void	philo_take_forks(t_lst_threads *man)
{
	pthread_mutex_lock(man->left);
	print_msg(man->print, get_timestamp(1), man->nbr, " has taken a fork");
	pthread_mutex_unlock(man->print);
	pthread_mutex_lock(man->right);
	print_msg(man->print, get_timestamp(1), man->nbr, " has taken a fork");
	pthread_mutex_unlock(man->print);
}

void	philo_eating(t_lst_threads *man)
{
	pthread_mutex_lock(&man->lock_eat);
	man->tstmp_eat = get_timestamp(1);
	man->tstmp_die = man->tstmp_eat + man->time_to_die;
	pthread_mutex_unlock(&man->lock_eat);
	print_msg(man->print, man->tstmp_eat, man->nbr, " is eating");
	pthread_mutex_unlock(man->print);
	man->times_eat++;
	wait_time(man->time_to_eat);
	pthread_mutex_unlock(man->right);
	pthread_mutex_unlock(man->left);
}

void	*life_philo(void *arg)
{
	t_lst_threads	*man;
	int				r;

	man = (t_lst_threads *)arg;
	r = pthread_create(&man->control_die, NULL, controller_die,
			(void *)man);
	if (r || pthread_detach(man->control_die))
		return (NULL);
	while (1)
	{
		philo_take_forks(man);
		philo_eating(man);
		print_msg(man->print, get_timestamp(1), man->nbr, " is sleeping");
		pthread_mutex_unlock(man->print);
		wait_time(man->time_to_sleep);
		print_msg(man->print, get_timestamp(1), man->nbr, " is thinking");
		pthread_mutex_unlock(man->print);
	}
	return (NULL);
}

void	*controller_die(void *arg)
{
	t_lst_threads		*man;
	unsigned long long	timer;

	man = (t_lst_threads *)arg;
	while (1)
	{
		pthread_mutex_lock(&man->lock_eat);
		timer = get_timestamp(1);
		if (timer > man->tstmp_die)
		{
			print_msg(man->print, timer, man->nbr, " died");
			pthread_mutex_unlock(man->dead);
			return (NULL);
		}
		pthread_mutex_unlock(&man->lock_eat);
		usleep(1000);
	}
	return (NULL);
}
