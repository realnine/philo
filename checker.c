#include "philo.h"

void	*checker_cnt(void *data)
{
	t_table	*table;
	int		i;
	int		cnt;

	table = (t_table *)data;
	i = 0;
	while (1)
	{
		if (table->philo_arr[i].cnt_eat >= table->num_must_eat
			&& table->philo_arr[i].all_ate == 0)
		{
			pthread_mutex_lock(&table->philo_arr[i].eat_mtx);
			table->philo_arr[i].all_ate = 1;
			//table->philo_arr[i].cnt_eat = 0;
			cnt++;
		}
		if (cnt >= table->num_philo)
			break ;
		if (++i >= table->num_philo)
			i = 0;
	}
	end_msg(END_COUNT, &table->philo_arr[0]);
	pthread_mutex_lock(&table->msg_mtx);
	pthread_mutex_unlock(&table->main_mtx);
	return (NULL);
}

void	*checker_death(void *data)
{
	t_philo	*philo;
	long	starv_time;

	philo = (t_philo *)data;
	while (1)
	{
		//pthread_mutex_lock(&philo->table->check_mtx);
		//pthread_mutex_unlock(&philo->table->check_mtx);
		pthread_mutex_lock(&philo->eat_mtx);
		if (philo->table->state == RUN && get_present_time() > philo->death_time)
		{
			
			//pthread_mutex_lock(&philo->table->check_mtx);
			end_msg(END_STARV, philo);
			//pthread_mutex_lock(&philo->table->msg_mtx); // 확인
			pthread_mutex_unlock(&philo->table->main_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->eat_mtx);
		usleep(1000);
	}
	return (NULL);
}
