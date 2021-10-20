#include "philo.h"

int	init_philo_arr(t_table *table)
{
	int	i;

	i = 0;
	table->philo_arr = (t_philo *)malloc(sizeof(t_philo) * table->num_p);
	if (!table->philo_arr)
		return (ERR);
	while (i < table->num_p)
	{
		table->philo_arr[i].index = i;
		table->philo_arr[i].table = table;
		table->philo_arr[i].lfork_idx = i;
		table->philo_arr[i].rfork_idx = (i + 1) % table->num_p;
		table->philo_arr[i].cnt_eat = 0;
		table->philo_arr[i].last_eat_time = get_present_time();
		i++;
	}
	return (0);
}

int	init_fork_mtx_arr(t_table *table)
{
	int	i;

	i = 0;
	table->fork_mtx_arr = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * table->num_p);
	if (!table->fork_mtx_arr)
		return (ERR);
	while (i < table->num_p)
	{
		if (pthread_mutex_init(&table->fork_mtx_arr[i], NULL))
			return (ERR);
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	table->state = RUNNING;
	if (init_philo_arr(table) == ERR)
		return (ERR);
	if (init_fork_mtx_arr(table) == ERR)
		return (ERR);
	if (pthread_mutex_init(&table->msg_mtx, NULL))
		return (ERR);
	return (0);
}
