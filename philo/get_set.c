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
