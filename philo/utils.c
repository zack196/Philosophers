/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:33:38 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/04 10:52:26 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(unsigned int slp, t_table *table)
{
	unsigned long	start;

	start = now();
	while (!get_int(table->table_mtx, &table->finish_sim))
	{
		if (now() - start >= slp)
			break ;
		usleep(table->nbr_philos * 3);
	}
}

long	now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("time function fealed!\n"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s2[i] - s1[i]);
}

void	record(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->table->record_mtx);
	if (!get_int(philo->table->table_mtx, &philo->table->finish_sim))
		printf("%ld %d %s\n", now() - philo->table->start_time, philo->id, str);
	pthread_mutex_unlock(philo->table->record_mtx);
}
