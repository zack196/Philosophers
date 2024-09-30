#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

typedef struct	s_philo	t_philo;

typedef struct	s_table
{
	int			nbr_philos;
	long		t2d;
	long		t2e;
	long		t2s;
	int			max_meal;
	long		start_time;
	t_philo		*philos;
	sem_t		*write_sem;
	sem_t		*forks;
	sem_t		*meal;
	sem_t		*death;
}	t_table;

struct s_philo
{
	int			id;
	int			meal_count;
	int			done;
	long		last_meal_time;
	t_table		*table;
	pid_t		pid;
	pthread_t	monitor_th;
};

void	eat(t_philo *philo);
void	*philo_monitor(void *arg);
void	routine(t_philo *philo);
int		get_int(sem_t *sem, int *val);
long	now(void);
void	ft_sleep(unsigned int slp, t_table *table);
void	routine_write(t_philo *philo, char *str);
long	ft_long(char *nb);
void	clean_up(t_table *table);
#endif