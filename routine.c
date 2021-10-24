#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	msg_print(L_FORK, philo);
	pthread_mutex_lock(philo->rfork);
	msg_print(R_FORK, philo);
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mtx);
	philo->cnt_eat++;
	msg_print(EAT, philo);
	philo->last_eat_time = get_present_time();
	philo->death_time = get_present_time() + philo->table->time_die;
	pthread_mutex_unlock(&philo->eat_mtx);
	ft_usleep(philo->table->time_eat);
}

int	sleep_and_think(t_philo *philo)
{
	msg_print(SLEEP, philo);
	ft_usleep(philo->table->time_sleep);
	msg_print(THINK, philo);
	return (0);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	trd;

	philo = (t_philo *)data;
	philo->last_eat_time = get_present_time();
	philo->death_time = get_present_time() + philo->table->time_die;
	if (pthread_create(&trd, NULL, &checker_death, data))
	{
		err_msg(ERR_MAIN4);
		return (NULL);
	}
	pthread_detach(trd);
	while (1)
	{
		take_fork(philo);
		eating(philo);
		put_fork(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
