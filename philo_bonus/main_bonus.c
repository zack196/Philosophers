/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 05:51:46 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/01 06:04:59 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_close(table->full);
	sem_unlink("/full");
	free(table->philos);
}

void	philo_feast(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nbr_philos)
		sem_wait(table->full);
	table->start_time = now();
	i = -1;
	while (++i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->pid = fork();
		if (philo->pid == -1)
		{
			printf("error creating a process\n");
			while (--i >= 0)
				kill(table->philos[i].pid, SIGKILL);
			return (clean_up(table));
		}
		else if (philo->pid == 0)
			routine(philo);
	}
	monitor_table(table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf("not enough argument\n"), 1);
	if (!init_table(&table, av))
		return (1);
	if (philosophers(&table))
		return (1);
	philo_feast(&table);
	clean_up(&table);
	return (0);
}
