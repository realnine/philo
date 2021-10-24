#include "philo.h"

int	make_philo(t_table *table, t_philo	*philo_arr)
{
	int			i;
	pthread_t	trd;

	table->start_time = get_present_time();
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&trd, NULL, &routine, &philo_arr[i]))
			return (ERR);
		pthread_detach(trd);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < table->num_philo)
	{
		if (pthread_create(&trd, NULL, &routine, &philo_arr[i]))
			return (ERR);
		pthread_detach(trd);
		i += 2;
	}
	return (0);
}

int	arg_check(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (err_msg(ERR_ARG1));
	table->num_philo = ft_atoi(argv[1]);
	if (table->num_philo < 1 || table->num_philo >= 200)
		return (err_msg(ERR_ARG2));
	table->time_die = ft_atoi(argv[2]);
	if (table->time_die < 60)
		return (err_msg(ERR_ARG3));
	table->time_eat = ft_atoi(argv[3]);
	if (table->time_eat < 60)
		return (err_msg(ERR_ARG4));
	table->time_sleep = ft_atoi(argv[4]);
	if (table->time_sleep < 60)
		return (err_msg(ERR_ARG5));
	if (argc == 6)
	{
		table->num_must_eat = ft_atoi(argv[5]);
		if (table->num_must_eat <= 0)
			return (err_msg(ERR_ARG6));
	}
	else
		table->num_must_eat = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	trd;

	if (arg_check(&table, argc, argv) == ERR)
		return (ERR);
	if (init_table(&table) == ERR)
		return (deallocate_all(&table) && err_msg(ERR_MAIN2));
	if (table.num_must_eat > 0)
		if (pthread_create(&trd, NULL, &checker_cnt, &table))
			return (deallocate_all(&table) && err_msg(ERR_MAIN4));
	if (make_philo(&table, table.philo_arr) == ERR)
		return (deallocate_all(&table) && err_msg(ERR_MAIN3));
	pthread_mutex_lock(&table.main_mtx);
	pthread_mutex_unlock(&table.main_mtx);
	deallocate_all(&table);
	return (0);
}
