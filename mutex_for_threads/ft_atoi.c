#include "philo_in_threads.h"

static int	len_number(const char *str)
{
	int	n;

	n = 0;
	while (str[n] >= '0' && str[n] <= '9')
		n++;
	return (n);
}

static int	check_sign(const char *str, int *i)
{
	if (str[*i] == '+')
		*i = *i + 1;
	else if (str[*i] == '-')
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}

unsigned long long	ft_atoi_llu(const char *nptr)
{
	int					i;
	unsigned long long	res;
	int					n;

	i = 0;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\f'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (check_sign(nptr, &i))
		return (0);
	n = len_number(&nptr[i]);
	if (n > 20 || n == 0)
		return (0);
	while (nptr[i + 1] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res + nptr[i++] - 48;
		res *= 10;
	}
	res = res + nptr[i] - 48;
	return (res);
}
