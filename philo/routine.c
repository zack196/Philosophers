/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:33:50 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/04 15:38:06 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	record(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	record(philo, "has taken a fork");
	pthread_mutex_lock(&philo->dead_mtx);
	philo->last_meal_time = now();
	record(philo, " is eating");
	philo->meal_count++;
	pthread_mutex_unlock(&philo->dead_mtx);
	ft_sleep(philo->table->t2e, philo->table);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->nbr_philos == 1)
		return (ft_sleep(table->t2d, table), record(philo, "died"), NULL);
	if (philo->id % 2 == 0)
		ft_sleep(30, table);
	while (!get_int(table->table_mtx, &table->finish_sim))
	{
		eat(philo);
		if (table->max_meals > 0 && get_int(&philo->dead_mtx, &philo->meal_count) >= table->max_meals)
		{
			set_int(table->table_mtx, &philo->is_done, 1);
			break ;
		}	
		record(philo, "is sleeping");
		ft_sleep(table->t2s, table);
		record(philo, " is thinking");
	}
	return (NULL);
}
