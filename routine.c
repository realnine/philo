#include "philo.h"

int	take_fork(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->fork_mtx_arr[philo->lfork_idx]);
	if (print_msg(L_FORK, philo) == STOP)
		return (STOP);
	pthread_mutex_lock(&table->fork_mtx_arr[philo->rfork_idx]);
	if (print_msg(R_FORK, philo) == STOP)
		return (STOP);
	return (0);
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_t	*fork_mtx_arr;

	fork_mtx_arr = philo->table->fork_mtx_arr;
	pthread_mutex_unlock(&fork_mtx_arr[philo->lfork_idx]);
	pthread_mutex_unlock(&fork_mtx_arr[philo->rfork_idx]);
}

int	eating(t_philo *philo)
{
	if (print_msg(EAT, philo) == STOP)
		return (STOP);
	usleep(philo->table->time_eat * 1000);
	philo->cnt_eat++;
	philo->last_eat_time = get_present_time();
	put_fork(philo);
	return (0);
}

int	sleep_and_think(t_philo *philo)
{
	if (print_msg(SLEEP, philo) == STOP)
		return (STOP);
	usleep(philo->table->time_sleep * 1000);
	if (print_msg(THINK, philo) == STOP)
		return (STOP);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (1)
	{
		if (take_fork(philo, table) == STOP)
			break ;
		if (eating(philo) == STOP)
			break ;
		if (sleep_and_think(philo) == STOP)
			break ;
	}
	return (NULL);
}
