/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_monitor_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 05:48:55 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/05 11:05:51 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_table(t_table *table)
{
	int	i;

	if (table->max_meal != -1)
	{
		i = -1;
		while (++i < table->nbr_philos)
			sem_wait(table->full);
		sem_post(table->death);
	}
	sem_wait(table->death);
	i = -1;
	while (++i < table->nbr_philos)
		kill(table->philos[i].pid, SIGKILL);
}

void eat(t_philo *philo)
{
    sem_wait(philo->table->forks); 
    routine_write(philo, "has taken a fork");
    sem_wait(philo->table->forks); 
    routine_write(philo, "has taken a fork");
    sem_wait(philo->table->meal);
    philo->last_meal_time = now();
    routine_write(philo, "is eating");
    philo->meal_count = philo->meal_count + 1;
    sem_post(philo->table->meal);
    ft_sleep(philo->table->t2e, philo->table);
    sem_post(philo->table->forks);
    sem_post(philo->table->forks);
}

void *philo_monitor(void *arg)
{
    t_philo *philo;
    int i;

    philo = (t_philo *)arg;
    while (1)
    {
        sem_wait(philo->table->meal);
        if (now() - philo->last_meal_time > philo->table->t2d && !philo->done)
        {
            routine_write(philo, "died");
            i = -1;
            while (++i < philo->table->nbr_philos)
                sem_post(philo->table->full);
            sem_post(philo->table->death);
            sem_post(philo->table->meal);
            break;
        }
        sem_post(philo->table->meal);
    }

    return (NULL);
}

void routine(t_philo *philo)
{
    if (pthread_create(&philo->monitor_th, NULL, philo_monitor, (void *)philo))
        return (clean_up(philo->table));
    // pthread_detach(philo->monitor_th);
    if (philo->table->nbr_philos == 1)
        return (ft_sleep(philo->table->t2d, philo->table));
    if (philo->id % 2 == 0)
        ft_sleep(30, philo->table);
    while (1)
    {
        eat(philo);
        if (philo->table->max_meal > 0 && philo->meal_count >= philo->table->max_meal)
        {
            philo->done = 1;
            sem_post(philo->table->full);
            sem_post(philo->table->meal);
            break;
        }
        routine_write(philo, "is sleeping");
        ft_sleep(philo->table->t2s, philo->table);
        routine_write(philo, "is thinking");
    }
    exit(0);
}
