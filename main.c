#include "philo.h"

int	make_and_execute_thread(t_table *table, t_philo	*philo_arr)
{
	int		i;

	table->start_time = get_present_time();
	i = 0;
	while (i < table->num_p)
	{
		if (pthread_create(&philo_arr[i].thr_id, NULL, routine, &philo_arr[i]))
			return (ERR);
		pthread_detach(philo_arr[i].thr_id);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < table->num_p)
	{
		if (pthread_create(&philo_arr[i].thr_id, NULL, routine, &philo_arr[i]))
			return (ERR);
		pthread_detach(philo_arr[i].thr_id);
		i += 2;
	}
	while (table->state == RUNNING)
		usleep(10);
	return (0);
}

void	release_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_p)
		pthread_mutex_destroy(&table->fork_mtx_arr[i++]);
	free(table->fork_mtx_arr);
	free(table->philo_arr);
	pthread_mutex_destroy(&table->msg_mtx);
}

int	arg_check(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (err_msg("wrong argc(rule : argc == 5 || argc == 6) \n"));
	table->num_p = ft_atoi(argv[1]);
	if (table->num_p < 2 || table->num_p > 300)
		return (err_msg("wrong num_philo(rule : philo >= 2 && philo <= 300)\n"));
	table->time_die = ft_atoi(argv[2]);
	if (table->time_die < 10)
		return (err_msg("wrong time to die (rule : time_die >= 10)\n"));
	table->time_eat = ft_atoi(argv[3]);
	if (table->time_eat < 10)
		return (err_msg("wrong time to eat (rule : time_eat >= 10)\n"));
	table->time_sleep = ft_atoi(argv[4]);
	if (table->time_sleep < 10)
		return (err_msg("wrong time to sleep (rule : time_sleep >= 10)\n"));
	if (argc == 6)
	{
		table->num_must_eat = ft_atoi(argv[5]);
		if (table->num_must_eat <= 0)
			return (err_msg("wrong cnt_must_eat(rule : cnt_must_eat > 0)\n"));
	}
	else
		table->num_must_eat = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (arg_check(&table, argc, argv) == ERR)
		return (ERR);
	if (init_table(&table) == ERR)
		return (ERR);
	if (make_and_execute_thread(&table, table.philo_arr) == ERR)
		return (ERR);
	release_table(&table);
	return (0);
}
