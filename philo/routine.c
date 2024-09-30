#include "philo.h"

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->r_fork);
    record(philo, "has taken a fork");
    pthread_mutex_lock(&philo->l_fork);
    record(philo, "has taken a fork");

    pthread_mutex_lock(&philo->dead_mtx);
    philo->last_meal_time = now();
    record(philo, " is eating");
    philo->meal_count++;
    pthread_mutex_unlock(&philo->dead_mtx);
    
    ft_sleep(philo->table->t2e, philo->table);

    pthread_mutex_unlock(&philo->l_fork);
    pthread_mutex_unlock(&philo->r_fork);
}

void	*routine(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    if (table->nbr_philos == 1)
        return (ft_sleep(table->t2d, table), NULL);
    if (philo->id % 2 == 0)
        ft_sleep(30, table);
    while (!get_int(&table->table_mtx, &table->finish_sim))
    {
        eat(philo);
        if (table->max_meals > 0 && philo->meal_count >= table->max_meals)
        {
            set_int(&table->table_mtx, &philo->is_done, 1);
            break ;
        }
        record(philo, "is sleeping");
        ft_sleep(table->t2s, table);
        record(philo, " is thinking");
    }
    return (NULL);
}



