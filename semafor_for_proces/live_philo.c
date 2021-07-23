#include "philo_in_proc.h"

void	philo_eating(t_proc *man, unsigned long long start)
{
	sem_wait(man->main->forks);
	print_msg(man->main->print, get_timestamp() - start, man->nbr,
		" has taken a fork");
	sem_post(man->main->print);
	sem_wait(man->main->forks);
	print_msg(man->main->print, get_timestamp() - start, man->nbr,
		" has taken a fork");
	sem_post(man->main->print);
	sem_wait(man->lock_eat);
	man->tstmp_eat = get_timestamp();
	man->tstmp_die = man->tstmp_eat + man->main->time_to_die;
	sem_post(man->lock_eat);
	print_msg(man->main->print, man->tstmp_eat - start, man->nbr,
		" is eating");
	sem_post(man->main->print);
	man->times_eat++;
	if (man->times_eat == man->main->times_must_eat)
		sem_post(man->main->end_eat[man->nbr - 1]);
	wait_time(man->main->time_to_eat);
}

void	philo_sleeping(t_proc *man, unsigned long long start)
{
	sem_post(man->main->forks);
	sem_post(man->main->forks);
	print_msg(man->main->print, get_timestamp() - start, man->nbr,
		" is sleeping");
	sem_post(man->main->print);
	wait_time(man->main->time_to_sleep);
}
