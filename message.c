#include "philo.h"

int	print_msg(int what, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->msg_mtx);
	if (check_stop(philo->table) == STOP)
		return (STOP);
	printf("%-8d", get_present_time() - philo->table->start_time);
	if (what == L_FORK)
		printf("[philo_" GREEN "%d" RESET
			"] has held [" BLUE "%d" RESET
			"] fork\n", philo->index, philo->lfork_idx);
	else if (what == R_FORK)
		printf("[philo_" GREEN "%d" RESET
			"] has held [" BLUE "%d" RESET
			"] fork\n", philo->index, philo->rfork_idx);
	else if (what == EAT)
	{
		printf("[philo_" GREEN "%d" RESET "] eating ", philo->index);
		printf(" (starv %dms)\n", get_present_time() - philo->last_eat_time);
	}
	else if (what == SLEEP)
		printf("[philo_" GREEN "%d" RESET "] is sleeping\n", philo->index);
	else if (what == THINK)
		printf("[philo_" GREEN "%d" RESET "] is thinking\n", philo->index);
	pthread_mutex_unlock(&philo->table->msg_mtx);
	return (0);
}

int	err_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (ERR);
}
