#include "philo.h"

int	take_fork(t_philo *philo, t_table *table)
{
	if (philo->table->state == STOP)
		return (0);
	pthread_mutex_lock(philo->lfork);
	act_msg(L_FORK, philo);
	pthread_mutex_lock(philo->rfork);
	act_msg(R_FORK, philo);
	return (0);
}

void	put_fork(t_philo *philo, t_table *table)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

int	eating(t_philo *philo, t_table *table)
{
	if (philo->table->state == STOP)
		return (0);
	pthread_mutex_lock(&philo->eat_mtx);
	philo->cnt_eat++;
	act_msg(EAT, philo);
	philo->last_eat_time = get_present_time();
	philo->death_time = get_present_time() + philo->table->time_die;
	pthread_mutex_unlock(&philo->eat_mtx);

	ft_usleep(philo->table->time_eat);

	put_fork(philo, table);
	return (0);
}

int	sleep_and_think(t_philo *philo, t_table *table)
{
	if (philo->table->state == STOP)
		return (0);
	act_msg(SLEEP, philo);
	ft_usleep(philo->table->time_sleep);
	act_msg(THINK, philo);
	return (0);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	checker_trd;

	philo = (t_philo *)data;
	philo->last_eat_time = get_present_time();
	philo->death_time = get_present_time() + philo->table->time_die;
	if (pthread_create(&checker_trd, NULL, &checker_death, data))
	{
		err_msg(ERR_MAIN4);
		return (NULL);
	}
	pthread_detach(checker_trd);
	while (1)
	{
		take_fork(philo, philo->table);
		eating(philo, philo->table);
		sleep_and_think(philo, philo->table);
	}
	return (NULL);
}
