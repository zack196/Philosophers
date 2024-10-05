/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:38:57 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/04 10:50:17 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_feast(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = now();
	while (++i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].th, NULL, routine
					, (void *)&table->philos[i]))
		{
			record(&table->philos[i], "error creating!");
			set_int(table->table_mtx, &table->finish_sim, 1);
			while (i--)
				pthread_join(table->philos[i].th, NULL);
			return (clean_up(table), 1);
		}
		pthread_mutex_lock(&table->philos[i].dead_mtx);
		table->philos[i].last_meal_time = now();
		pthread_mutex_unlock(&table->philos[i].dead_mtx);
	}
	monitoring(table);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philos[i].th, NULL);
	return (0);
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
	table->table_mtx && pthread_mutex_destroy(table->table_mtx);
	table->record_mtx && pthread_mutex_destroy(table->record_mtx);
	free(table->forks);
	table->forks = NULL;
	free(table->table_mtx);
	table->table_mtx = NULL;
	free(table->record_mtx);
	table->record_mtx = NULL;
	free(table->philos);
	table->philos = NULL;
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf("not enough arguments!\n"), 1);
	if (!init_table(&table, av))
		return (1);
	if (philo_feast(&table))
		return (1);
	clean_up(&table);
	return (0);
}
