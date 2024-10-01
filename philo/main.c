/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:38:57 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/01 04:11:54 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_feast(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = now();
	while (++i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].th, NULL, routine
				, (void *)&table->philos[i]))
		{
			while (i-- >= 0)
				pthread_join(table->philos[i].th, NULL);
			return ;
		}
		table->philos[i].last_meal_time = now();
	}
	monitoring(table);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philos[i].th, NULL);
	if (table->time_of_death != -1)
		printf("%ld %d died\n", table->time_of_death, table->dead_philo_id);
}

void	clean_up(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].dead_mtx);
	}
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->record_mtx);
	free(table->forks);
	free(table->philos);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf("not enough arguments!\n"), 1);
	if (!init_table(&table, av))
		return (1);
	philo_feast(&table);
	clean_up(&table);
	return (0);
}
