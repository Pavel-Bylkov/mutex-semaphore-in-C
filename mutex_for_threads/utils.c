#include "philo_in_threads.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	fail(char *str, int code)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (code);
}

void	ft_putnbr_fd(unsigned long long nbr, int fd)
{
	char	buf[25];
	int		len;

	len = 24;
	buf[len--] = '\0';
	if (nbr == 0)
		buf[len--] = '0';
	while (nbr != 0)
	{
		buf[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	write(fd, &buf[len + 1], ft_strlen(&buf[len + 1]));
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void	print_msg(t_mutex *p, unsigned long long t, unsigned int n, char *msg)
{
	int							len;

	len = ft_strlen(msg);
	pthread_mutex_lock(p);
	ft_putnbrf_fd(t, 1);
	write(1, " ", 1);
	ft_putnbr_fd(n, 1);
	write(1, msg, len);
	write(1, "\n", 1);
}
