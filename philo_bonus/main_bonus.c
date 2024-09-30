#include "philo_bonus.h"

int	init_sem(t_table *table)
{
    sem_unlink("/write");
    sem_unlink("/forks");
    sem_unlink("/death");
    sem_unlink("/meal");
    table->meal = sem_open("/meal", O_CREAT, 0644, 1);
    if (table->meal == SEM_FAILED)
        return (1);
	table->death = sem_open("/death", O_CREAT, 0644, 0);
    if (table->death == SEM_FAILED)
        return (1);
    table->write_sem = sem_open("/write", O_CREAT, 0644, 1);
    if (table->write_sem == SEM_FAILED)
        return (1);
    table->forks = sem_open("/forks", O_CREAT, 0644, table->nbr_philos);
    if (table->forks == SEM_FAILED)
        return (1);
	return (0);
}

int init_table(t_table *table, char **av)
{
    table->nbr_philos = ft_long(av[1]);
    table->t2d = ft_long(av[2]);
    table->t2e = ft_long(av[3]);
    table->t2s = ft_long(av[4]);
    table->max_meal = -1;
    if (av[5])
        table->max_meal = ft_long(av[5]);
    table->philos = NULL;
	if (init_sem(table))
		return (clean_up(table), 0);
    return (table->nbr_philos && table->t2d && table->t2e
            && table->t2s && table->max_meal);
}

int	philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philos = malloc(sizeof (t_philo) * table->nbr_philos);
	if (!table->philos)
		return (clean_up(table), 1);
	i = -1;
	while (++i <table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meal_count = 0;
		philo->table = table;
	}	
	return (0);
}
void	clean_up(t_table *table)
{
	sem_close(table->forks);
	sem_unlink("/forks");
	sem_close(table->death);
	sem_unlink("/death");
	sem_close(table->write_sem);
	sem_unlink("/write");
	sem_close(table->meal);
	sem_unlink("/meal");
	free(table->philos);
}

void	philo_feast(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	table->start_time = now();
	while (++i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->pid = fork();
		if (philo->pid == -1)
		{
			while (--i >= 0)
				kill(table->philos[i].pid, SIGKILL);
			return (clean_up(table));
		}
		else if (philo->pid == 0)
			routine(philo);
	}
	sem_wait(table->death);
	i = -1;
	while (++i < table->nbr_philos)
		kill(table->philos[i].pid, SIGKILL);
}

int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
        return (1);
    if (!init_table(&table, av))
		return (1);
	if (philosophers(&table))
		return (1);
	philo_feast(&table);
	clean_up(&table);
	return (0);
}
