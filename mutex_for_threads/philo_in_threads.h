#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> /* usleep */
# include <stdio.h> /* printf */
# include <stdlib.h> /* malloc free */
# include <sys/time.h> /* gettimeofday */
# include <pthread.h> /* pthread_create */
# include <string.h> /* memset */

# define TIK 50

typedef pthread_mutex_t	t_mutex;

typedef struct s_lst_threads
{
	pthread_t				thread;
	pthread_t				control_die;
	unsigned int			nbr;
	unsigned long long		time_to_die;
	unsigned long long		time_to_eat;
	unsigned long long		time_to_sleep;
	unsigned int			times_eat;
	unsigned long long		tstmp_eat;
	unsigned long long		tstmp_die;
	t_mutex					*left;
	t_mutex					*right;
	t_mutex					*print;
	t_mutex					lock_eat;
	t_mutex					*lock_forks;
	t_mutex					*dead;
	struct s_lst_threads	*next;
}				t_lst_threads;

typedef struct s_philo
{
	unsigned int		number_of_philos;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned int		times_must_eat;
	pthread_t			control_eat;
	t_mutex				lock_forks;
	t_mutex				*forks;
	t_lst_threads		*threads;
	t_mutex				print;
	t_mutex				dead;
}				t_philo;

int					ft_strlen(char *str);
int					fail(char *str, int code);
unsigned long long	ft_atoi_llu(const char *nptr);
void				ft_putnbr_fd(unsigned long long nbr, int fd);
void				ft_putnbrf_fd(unsigned long long nbr, int fd);
void				ft_putstr_fd(char *str, int fd);
void				*life_philo(void *arg);
void				*controller_die(void *arg);
void				*controller_eat(void *arg);
t_lst_threads		*new_thread(t_philo *philo);
int					thread_add_back(t_philo *philo, t_lst_threads *new);
int					threads_start(t_philo *philo, int r);
int					start_control(t_philo *philo);
int					cleaner(t_philo *philo, int code);
void				print_msg(t_mutex *p, unsigned long long t, unsigned int n,
						char *msg);
unsigned long long	get_timestamp(int f);
void				wait_time(unsigned long long time);

#endif
