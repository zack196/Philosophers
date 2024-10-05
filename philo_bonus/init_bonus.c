/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 06:00:58 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/04 13:52:27 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (table->max_meal != -1)
	{
		sem_unlink("/full");
		table->full = sem_open("/full", O_CREAT, 0644, table->nbr_philos);
		if (table->full == SEM_FAILED)
			return (1);
	}
	return (0);
}

int	init_table(t_table *table, char **av)
{
	table->nbr_philos = ft_long(av[1]);
	table->t2d = ft_long(av[2]);
	table->t2e = ft_long(av[3]);
	table->t2s = ft_long(av[4]);
	table->max_meal = -1;
	if (av[5])
		table->max_meal = ft_long(av[5]);
	if (!(table->nbr_philos && table->t2d && table->t2e
			&& table->t2s && table->max_meal))
		return (printf("argumet should be int\n"), 0);
	table->philos = NULL;
	if (init_sem(table))
		return (clean_up(table), printf("error init semaphores\n"), 0);
	return (1);
}

int	philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philos = malloc(sizeof (t_philo) * table->nbr_philos);
	if (!table->philos)
		return (clean_up(table), printf("error malloc\n"), 1);
	i = -1;
	while (++i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meal_count = 0;
		philo->table = table;
	}
	return (0);
}
