#include "philo.h"

int	act_msg(int what, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->msg_mtx);
	if (philo->table->state == STOP)
		return (0);
	printf("%-8d", get_present_time() - philo->table->start_time);
	if (what == L_FORK)
		printf(G"%-3d"RS" has taken ["B"%d"RS"]lfork\n", philo->index, philo->lfork_idx);
	else if (what == R_FORK)
		printf(G"%-3d"RS" has taken ["B"%d"RS"]rfork\n", philo->index, philo->rfork_idx);
	else if (what == EAT)
	{
		printf(G"%-3d"RS" eating (ate %d time),", philo->index, philo->cnt_eat);
		printf(" (starv %dms)\n", get_present_time() - philo->last_eat_time);
	}
	else if (what == SLEEP)
		printf(G"%-3d"RS" is sleeping\n", philo->index);
	else if (what == THINK)
		printf(G"%-3d"RS" is thinking\n", philo->index);
	pthread_mutex_unlock(&philo->table->msg_mtx);
	return (0);
}

int end_msg(int what, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->msg_mtx);
	if (philo->table->state == STOP)
		return (0);
	printf("%-8d", get_present_time() - philo->table->start_time);
	if (what == END_COUNT)
		printf(R "All philosophers ate their quota" RS "\n");
	else if (what == END_STARV)
	{
		printf(G "%-3d"RS R" died" RS, philo->index);
		printf(" (starv %dms)\n", get_present_time() - philo->last_eat_time);
	}
	philo->table->state = STOP;
	pthread_mutex_unlock(&philo->table->msg_mtx);
	return (0);
}

int	err_msg(int what)
{
	char *msg;
	if (what == ERR_ARG1)
		msg = "wrong argc(rule : argc == 5 || argc == 6) \n";
	else if (what == ERR_ARG2)
		msg = "wrong num_philo(rule : philo >= 1 && philo < 200)\n";
	else if (what == ERR_ARG3)
		msg = "wrong time to die (rule : time_die >= 60)\n";
	else if (what == ERR_ARG4)
		msg = "wrong time to eat (rule : time_eat >= 60)\n";
	else if (what == ERR_ARG5)
		msg = "wrong time to sleep (rule : time_sleep >= 60)\n";
	else if (what == ERR_ARG6)
		msg = "wrong cnt_must_eat(rule : cnt_must_eat > 0)\n";
	else if (what == ERR_MAIN1)
		msg = "arg error\n";
	else if (what == ERR_MAIN2)
		msg = "init_table error\n";
	else if (what == ERR_MAIN3)
		msg = "make_philo error\n";
	else if (what == ERR_MAIN4)
		msg = "make_ckecker error\n";
	write(2, msg, ft_strlen(msg));
	return (ERR);
}

void	tmp_print(char *str, t_philo *philo, int starv)
{
	pthread_mutex_lock(&philo->table->msg_mtx);
	printf("%-8d", get_present_time() - philo->table->start_time);
	printf("[%d] %s (starv : %d)\n", philo->index, str, starv);
	pthread_mutex_unlock(&philo->table->msg_mtx);
}