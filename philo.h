#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>  
# include <stdlib.h>
# include <unistd.h>   //sleep, usleep, write
# include <pthread.h>
# include <sys/time.h>  // get time of day

# define RED	"\x1b[1;31m"
# define GREEN	"\x1b[1;32m"
# define BLUE	"\x1b[1;34m"
# define RESET	"\x1b[0m"

// table->state val & routine functions's rtn val
# define RUNNING	0
# define STOP		1

// print_msg() input val
# define L_FORK		1
# define R_FORK		2
# define EAT		3
# define SLEEP		4
# define THINK		5
# define END_COUNT	6
# define END_STARV	7

// main functions rtn val
# define ERR		1

typedef struct s_philo //threads
{
	pthread_t		thr_id;
	int				index;
	int				last_eat_time;
	int				lfork_idx;
	int				rfork_idx;
	int				cnt_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_p;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;

	int				state;
	int				start_time;
	t_philo			*philo_arr;

	pthread_mutex_t	eat_mtx;
	pthread_mutex_t	msg_mtx;
	pthread_mutex_t	check_stop_mtx;
	pthread_mutex_t	*fork_mtx_arr;
}	t_table;

// utils.c
int		ft_strlen(char const *str);
int		ft_atoi(char const *str);
void	ft_putnbr_fd(uint64_t n, int fd);
int		get_present_time(void);

// message.c
int		err_msg(char *msg);
int		print_msg(int what, t_philo *philo);

// init.c
int		init_table(t_table *table);

// routine.c
void	*routine(void *data);

// check_stop.c
int		check_stop(t_table *table);

#endif