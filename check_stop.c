#include "philo.h"

int	check_cnt(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_p)
	{
		if (table->philo_arr[i].cnt_eat < table->num_must_eat)
			break ;
		i++;
	}
	if (i == table->num_p)
	{
		printf("%-8d", get_present_time() - table->start_time);
		printf(RED "All philosophers ate their quota" RESET "\n");
		table->state = STOP;
		return (STOP);
	}
	return (0);
}

int	check_time(t_table *table)
{
	long	starv_time;
	int		i;

	starv_time = 0;
	i = 0;
	while (i < table->num_p)
	{
		starv_time = get_present_time() - table->philo_arr[i].last_eat_time;
		if (starv_time >= table->time_die)
		{
			printf("%-8d", get_present_time() - table->start_time);
			printf("[philo_" GREEN "%d" RESET "]" RED
				" starved to death" RESET, table->philo_arr[i].index);
			printf(" (starv_time : %ldms)\n", starv_time);
			table->state = STOP;
			return (STOP);
		}
		i++;
	}
	return (0);
}

int	check_stop(t_table *table)
{
	pthread_mutex_lock(&table->check_stop_mtx);
	if (table->num_must_eat > 0)
	{
		if (check_cnt(table) == STOP)
			return (STOP);
	}
	if (check_time(table) == STOP)
		return (STOP);
	pthread_mutex_unlock(&table->check_stop_mtx);
	return (0);
}
