/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:38:39 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/01 03:38:44 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_int(pthread_mutex_t *mtx, int *val)
{
	int	res;

	pthread_mutex_lock(mtx);
	res = *val;
	pthread_mutex_unlock(mtx);
	return (res);
}

void	set_int(pthread_mutex_t *mtx, int *dest, int val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

long	get_long(pthread_mutex_t *mtx, long *val)
{
	long	res;

	pthread_mutex_lock(mtx);
	res = *val;
	pthread_mutex_unlock(mtx);
	return (res);
}

void	set_long(pthread_mutex_t *mtx, long *dest, long val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}
