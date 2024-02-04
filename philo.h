#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <time.h>

typedef enum s_fork{
	available,
	in_use
}	t_fork;

typedef struct s_philo
{
	int	id;
	int eat;
	pthread_t thread;
	struct s_table *table;
	t_fork self_fork;
	t_fork *other_fork;
}	t_philo;

typedef struct s_table
{
	int		d_time;
	int 	e_time;
	int 	s_time;
	int		p_count;
	int 	e_count;
	long long start;
	t_philo *philo;
	pthread_mutex_t mutex;
}	t_table;

int		ft_atoi(char *str);
void	error_msg(char *str);
void	free_table(t_table *tab);
int		check_all(char **av, int count);

#endif