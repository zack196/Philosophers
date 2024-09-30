#include "philo_bonus.h"

int	get_int(sem_t *sem, int *val)
{
	int	res;

	sem_wait(sem);
	res = *val;
	sem_post(sem);
	return (res);
}

long	now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("time function fealed!\n"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(unsigned int slp, t_table *table)
{
	unsigned long	start;

	start = now();
	while (1)
	{
		if (now() - start >= slp)
			break ;
		usleep(table->nbr_philos * 3);
	}
}

void	routine_write(t_philo *philo, char *str)
{ 
	sem_wait(philo->table->write_sem);
	printf("%ld %d %s\n", now() - philo->table->start_time, philo->id, str);
	if (*str != 'd')
		sem_post(philo->table->write_sem);
}

long	ft_long(char *nb)
{
	long	l;
	int		i;

	l = 0;
	i = 0;
	while ((9 <= nb[i] && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
		if (nb[i++] == '-')
			return (0);
	while ('0' <= nb[i] && nb[i] <= '9')
	{
		l = l * 10 + (nb[i] - '0');
		i++;
	}
	if (nb[i])
		return (0);
	return (l);
}