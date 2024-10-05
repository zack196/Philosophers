/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:36:09 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/04 10:43:31 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philo_full(t_table *table)
{
	int		i;
	int		full;
	t_philo	*philo;

	i = -1;
	full = 0;
	while (++i < table->nbr_philos)
	{
		philo = &table->philos[i];
		if (get_int(table->table_mtx, &philo->is_done))
			full++;
	}
	if (full == table->nbr_philos)
	{
		set_int(table->table_mtx, &table->finish_sim, 1);
		return (1);
	}
	return (0);
}

int	one_philo_die(t_table *table)
{
	int		i;
	long	delta_t;
	t_philo	*philo;

	i = -1;
	while (++i < table->nbr_philos)
	{
		philo = &table->philos[i];
		pthread_mutex_lock(&philo->dead_mtx);
		delta_t = now() - philo->last_meal_time;
		if (delta_t > table->t2d && !philo->is_done)
		{
			record(philo, "died");
			set_int(table->table_mtx, &table->finish_sim, 1);
			pthread_mutex_unlock(&philo->dead_mtx);
			return (1);
		}
		pthread_mutex_unlock(&philo->dead_mtx);
	}
	return (0);
}

void	monitoring(t_table *table)
{
	if (table->nbr_philos == 1)
		return ;
	while (1)
	{
		if (all_philo_full(table) || one_philo_die(table))
			break ;
	}
}
