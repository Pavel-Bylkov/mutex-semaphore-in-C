#include "philo_in_threads.h"

void	lst_thread_clean(t_lst_threads	**lst)
{
	t_lst_threads	*tmp;
	t_lst_threads	*head;

	head = *lst;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	*lst = NULL;
}

int	cleaner(t_philo *philo, int code)
{
	unsigned int	i;

	i = 0;
	while (i < philo->number_of_philos)
		pthread_mutex_destroy(&philo->forks[i++]);
	free(philo->forks);
	if (philo->threads)
		lst_thread_clean(&philo->threads);
	pthread_mutex_destroy(&philo->print);
	pthread_mutex_destroy(&philo->lock_forks);
	pthread_mutex_destroy(&philo->dead);
	get_timestamp(0);
	return (code);
}
