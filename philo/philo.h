/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:35:19 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/01 06:05:47 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int				nbr_philos;
	long			t2d;
	long			t2e;
	long			t2s;
	int				max_meals;
	long			start_time;
	int				finish_sim;
	long			time_of_death;
	int				dead_philo_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	table_mtx;
	pthread_mutex_t	record_mtx;
	t_philo			*philos;
}	t_table;

struct	s_philo
{
	t_table			*table;
	int				id;
	pthread_t		th;
	int				is_done;
	int				meal_count;
	long			last_meal_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	dead_mtx;
};

void	clean_up(t_table *table);
int		init_table(t_table *table, char **av);
void	*routine(void *arg);
void	monitoring(t_table *table);
long	now(void);
void	ft_sleep(unsigned int slp, t_table *table);
void	record(t_philo *philo, char *str);
int		get_int(pthread_mutex_t *mtx, int *val);
void	set_int(pthread_mutex_t *mtx, int *dest, int val);
long	get_long(pthread_mutex_t *mtx, long *val);
void	set_long(pthread_mutex_t *mtx, long *dest, long val);
#endif