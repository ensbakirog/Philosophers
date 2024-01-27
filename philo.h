#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

typedef struct s_philo
{
	int	philo_id;
	pthread_t *thread;
}	t_philo;

typedef struct s_table
{
	int		death_time;
	int 	eating_time;
	int 	sleeping_time;
	int		p_count;
	int 	eating_count;
	t_philo **philo;
}	t_table;

int		ft_atoi(char *str);
void	error_msg(char *str);

#endif