#include "philo.h"

void	free_fork_m(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->fork_mtx_arr[i]);
		i++;
	}
	return ;
}

void	free_eat_m(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->philo_arr[i].eat_mtx);
		i++;
	}
	return ;
}

int	deallocate_all(t_table *table)
{
	free_fork_m(table);
	free_eat_m(table);

	free(table->fork_mtx_arr);
	free(table->philo_arr);

	pthread_mutex_destroy(&table->msg_mtx);
	pthread_mutex_destroy(&table->main_mtx);
	return (1);
}