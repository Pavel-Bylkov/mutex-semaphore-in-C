#include "philo_in_proc.h"

unsigned long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * (unsigned long long)1000
		+ t.tv_usec / (unsigned long long)1000);
}

void	wait_time(unsigned long long time)
{
	unsigned long long	start;
	unsigned long long	end;

	start = get_timestamp();
	usleep((time - 5) * 1000);
	while (1)
	{
		usleep(50);
		end = get_timestamp();
		if (end - start >= time)
			return ;
	}
}

void	ft_putnbrf_fd(unsigned long long nbr, int fd)
{
	char	buf[25];
	int		len;

	len = 24;
	memset(buf, '0', sizeof(buf));
	buf[len--] = '\0';
	while (nbr != 0)
	{
		buf[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (len < 10)
		write(fd, &buf[len + 1], ft_strlen(&buf[len + 1]));
	else
		write(fd, &buf[11], 13);
}
