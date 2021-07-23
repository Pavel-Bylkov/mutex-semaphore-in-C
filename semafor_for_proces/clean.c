#include "philo_in_proc.h"

void	close_sema(sem_t *sem, char *sem_name)
{
	sem_close(sem);
	sem_unlink(sem_name);
}

int	cleaner(t_main *main, int code)
{
	unsigned int	i;
	t_proc			*tmp;

	close_sema(main->forks, S_FORK);
	close_sema(main->print, S_PRINT);
	close_sema(main->dead, S_DEAD);
	i = 0;
	if (main->philos)
	{
		while (i < main->number_of_philos)
		{
			tmp = &main->philos[i];
			close_sema(tmp->lock_eat, tmp->s_name);
			free(tmp->s_name);
			if (main->end_eat && main->end_eat[i])
				close_sema(main->end_eat[i++], tmp->s_name_end);
			free(tmp->s_name_end);
			if (tmp->pid)
				kill(tmp->pid, SIGKILL);
		}
		free(main->philos);
	}
	free(main->end_eat);
	return (code);
}
