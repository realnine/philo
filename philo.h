#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>  
# include <stdlib.h>
# include <unistd.h>   //sleep, usleep, write
# include <pthread.h>
# include <sys/time.h>  // get time of day

# define R	"\x1b[1;31m"
# define G	"\x1b[1;32m"
# define B	"\x1b[1;34m"
# define RS	"\x1b[0m"

// main return val
# define ERR		1

// table->state val
# define RUN		1
# define STOP		2

// act_msg val
# define L_FORK		4
# define R_FORK		5
# define EAT		6
# define SLEEP		7
# define THINK		8

// end_msg val
# define END_COUNT	9
# define END_STARV	10

// err_msg val
# define ERR_ARG1	1
# define ERR_ARG2	2
# define ERR_ARG3	3
# define ERR_ARG4	4
# define ERR_ARG5	5
# define ERR_ARG6	6
# define ERR_MAIN1	7
# define ERR_MAIN2	8
# define ERR_MAIN3	9
# define ERR_MAIN4	10

typedef struct s_philo
{
	pthread_t		thr_id;
	int				index;
	int				last_eat_time;
	int				death_time;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				lfork_idx;
	int				rfork_idx;
	int				cnt_eat;
	int				all_ate;
	struct s_table	*table;
	pthread_mutex_t	eat_mtx;

}	t_philo;

typedef struct s_table
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;

	int				start_time;
	t_philo			*philo_arr;
	pthread_mutex_t	*fork_mtx_arr;

	pthread_mutex_t	msg_mtx;
	pthread_mutex_t	main_mtx;

	int				state;
}	t_table;

// utils.c
int		ft_strlen(char const *str);
int		ft_atoi(char const *str);
int		get_present_time(void);
void	ft_usleep(int spend_time);

// msg.c
int		err_msg(int what);
int		act_msg(int what, t_philo *philo);
int		end_msg(int what, t_philo *philo);

// init.c
int		init_table(t_table *table);

// routine.c
void	*routine(void *data);

// checker.c
void	*checker_death(void *data);
void	*checker_cnt(void *data);

//release_table.c
int		deallocate_all(t_table *table);

#endif
