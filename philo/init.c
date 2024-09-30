#include "philo.h"

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

void	init_philo(t_table *table)
{
	t_philo	*philo;
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->is_done = 0;
		philo->table = table;
		philo->r_fork = table->forks[i];
		philo->l_fork = table->forks[(i + 1) % table->nbr_philos];
	}
}
int	init_mtx(t_table *table)
{
    int i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philos[i].dead_mtx, NULL);
	}
	pthread_mutex_init(&table->table_mtx, NULL);
	pthread_mutex_init(&table->record_mtx, NULL);
	i = -1;
	return (0);
}

int	init_table(t_table *table, char **av)
{
	table->nbr_philos = ft_long(av[1]);
	table->t2d = ft_long(av[2]);
	table->t2e = ft_long(av[3]);
	table->t2s = ft_long(av[4]);
	table->max_meals = -1;
	if (av[5])
	{
		table->max_meals = ft_long(av[5]);
		if (!table->max_meals)
			return (0);
	}
	table->finish_sim = 0;
	table->time_of_death = -1;
	table->philos = malloc(sizeof (t_philo) * table->nbr_philos);
	if (!table->philos || !table->nbr_philos)
		return (free(table->philos), 0);
	table->forks = malloc(sizeof (pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
		return (free(table->philos), 0);
    if (init_mtx(table))
        return (free(table->forks), free(table->philos), 0);
	init_philo(table);
	return (table->nbr_philos && table->t2d && table->t2e && table->t2s);
}
