/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geters_seters_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:30:13 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/04 13:30:15 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long    get_long(sem_t *sem, long *dest)
{
    long res;

    sem_wait(sem);
    res = *dest;
    sem_post(sem);
    return (res);
}

void    set_int(sem_t *sem, int *dest, int val)
{
    sem_wait(sem);
    *dest = val;
    sem_post(sem);
}

void    set_long(sem_t *sem, long *dest, long val)
{
    sem_wait(sem);
    *dest = val;
    sem_post(sem);
}
