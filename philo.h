#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

typedef struct s_philo
{
	int	philo_id;
	pthread_t *thread;
}	t_philo;

int	ft_atoi(char *str);

#endif