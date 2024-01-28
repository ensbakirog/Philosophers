#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <time.h>

typedef struct s_philo
{
	int	philo_id;
	int philo_eat;
	int last_eat;
	pthread_t thread;
}	t_philo;

typedef struct s_table
{
	int		death_time;
	int 	eating_time;
	int 	sleeping_time;
	int		p_count;
	int 	eating_count;
	int		last_id;
	t_philo **philo;
	pthread_mutex_t mutex;
	struct timeval time;
}	t_table;

int		ft_atoi(char *str);
void	error_msg(char *str);
void	free_table(t_table *tab);
int		check_all(char **av, int count);
void	error_free(char *str, t_table *tab);

#endif