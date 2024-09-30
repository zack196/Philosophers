#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->table->forks);
	routine_write(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	routine_write(philo, "has taken a fork");

	sem_wait(philo->table->meal);
	philo->last_meal_time = now();
	routine_write(philo, "is eating");
	philo->meal_count++;
	sem_post(philo->table->meal);

	ft_sleep(philo->table->t2e, philo->table);

	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	*philo_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->table->meal);
		if (now() - philo->last_meal_time > philo->table->t2d && !philo->done)
		{
			routine_write(philo, "died");
			sem_post(philo->table->death);
			sem_post(philo->table->meal);
			break ;
		}
		sem_post(philo->table->meal);
		// if (get_int(philo->table->meal, &philo->done))
		// 	break;
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	philo->last_meal_time = now();
	if (pthread_create(&philo->monitor_th, NULL, philo_monitor, (void *)philo))
		return (clean_up(philo->table));
	if (philo->table->nbr_philos == 1)
		return (ft_sleep(philo->table->t2d, philo->table));
	if (philo->id % 2 == 0)
		ft_sleep(30, philo->table);
	while (1)
	{
		eat(philo);
		if (philo->table->max_meal > 0 
			&& philo->meal_count >= philo->table->max_meal)
		{
			sem_wait(philo->table->meal);
			philo->done = 1;
			sem_post(philo->table->meal);
            sem_post(philo->table->death);
			break ;
		}
		routine_write(philo, "is sleeping");
		ft_sleep(philo->table->t2s, philo->table);
		routine_write(philo, "is thiinking");
	}
	pthread_join(philo->monitor_th, NULL);
	exit(0);
}
