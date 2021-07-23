#ifndef PHILO_PROC_H
# define PHILO_PROC_H

# include <sys/types.h> /* fork */
# include <unistd.h>
# include <stdio.h> /* printf */
# include <stdlib.h> /* malloc free */
# include <sys/time.h> /* gettimeofday */
# include <pthread.h> /* pthread_create */
# include <string.h> /* memset */
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h> /* kill */

# define S_FORK "/s_fork"
# define S_PRINT "/s_print"
# define S_DEAD "/s_dead"
# define S_EAT "/s_eat_"
# define S_ENDEAT "/s_endeat_"

struct	s_main;

typedef struct s_proc
{
	unsigned int		nbr;
	unsigned int		times_eat;
	unsigned long long	tstmp_eat;
	unsigned long long	tstmp_die;
	pid_t				pid;
	pthread_t			control_die;
	char				*s_name;
	char				*s_name_end;
	sem_t				*lock_eat;
	struct s_main		*main;
}						t_proc;

typedef struct s_main
{
	unsigned int		number_of_philos;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned int		times_must_eat;
	unsigned long long	tstmp_start;
	t_proc				*philos;
	pthread_t			control_eat;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*dead;
	sem_t				**end_eat;
}						t_main;

unsigned long long	ft_atoi_llu(const char *nptr);
int					ft_strlen(char *str);
int					fail(char *str, int code);
void				ft_putnbr_fd(unsigned long long nbr, int fd);
void				ft_putnbrf_fd(unsigned long long nbr, int fd);
void				ft_putstr_fd(char *str, int fd);
char				*ft_itoa(long long int n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *str);
char				*ft_strdupn(const char *str, size_t len);
int					start_control(t_main *philo);
void				*controller_eat(void *arg);
void				*controller_die(void *arg);
unsigned long long	get_timestamp(void);
void				wait_time(unsigned long long time);
int					init_sema(t_main *main);
int					init_philos(t_proc *philo, int i, t_main *main);
void				philo_eating(t_proc *man, unsigned long long start);
void				philo_sleeping(t_proc *man, unsigned long long start);
void				print_msg(sem_t *print, unsigned long long t,
						unsigned int n, char *msg);
int					cleaner(t_main *main, int code);

#endif
