#include "philo.h"

void	*checker_cnt(void *data)
{
	t_table	*table;
	int		i;
	int		cnt;

	table = (t_table *)data;
	i = 0;
	cnt = 0;
	while (1)
	{
		if (table->philo_arr[i].cnt_eat >= table->num_must_eat
			&& table->philo_arr[i].all_ate == 0)
		{
			pthread_mutex_lock(&table->philo_arr[i].eat_mtx);
			table->philo_arr[i].all_ate = 1;
			cnt++;
		}
		if (cnt >= table->num_philo)
			break ;
		if (++i >= table->num_philo)
			i = 0;
	}
	msg_print(END_COUNT, &table->philo_arr[0]);
	pthread_mutex_lock(&table->msg_mtx);
	pthread_mutex_unlock(&table->main_mtx);
	return (NULL);
}

void	*checker_death(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->eat_mtx);
		if (philo->table->state == RUN
			&& get_present_time() > philo->death_time)
		{
			msg_print(END_STARV, philo);
			pthread_mutex_unlock(&philo->table->main_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->eat_mtx);
		usleep(1000);
	}
}
