#include <unistd.h>
#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

long	get_time(t_table *tab);

void	is_sleeping(t_table *tab)
{
	long	time;

	time = get_time(tab);
	printf("%ld %d is sleeping\n", time, tab->last_id);
	usleep(tab->sleeping_time);
}

void * life_loop(void *arg)
{
	is_sleeping(arg);
	return (NULL);
}

long	get_time(t_table *tab)
{
	long time;
	if (gettimeofday(&tab->time, NULL) != 0)
		return (error_free("Time error", tab), -1); 
	time = tab->time.tv_sec;
	return (time);
}


int create_philo(t_table *tab)
{
	int i;

	i = -1;
	tab->philo = (t_philo **)malloc(sizeof(t_philo *) * tab->p_count);
	if (tab->philo == NULL)
		return (error_free("Malloc error", tab), -1);
	while (++i < tab->p_count)
	{
		tab->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (tab->philo[i] == NULL)
			return (error_free("Malloc error", tab), -1);
		tab->philo[i]->philo_id = i + 1;
		tab->last_id = i + 1;
		if (pthread_create(&tab->philo[i]->thread, NULL, &life_loop, tab) != 0)
			return (error_free("Pthread create", tab), -1);
		if (pthread_join(tab->philo[i]->thread, NULL) != 0)
			return (error_free("Pthread join", tab), -1);
	}
	return (0);
}

void	assign_arg(char **av, int count, t_table *tab)
{
	tab->p_count = ft_atoi(av[0]);
	tab->death_time = ft_atoi(av[1]);
	tab->eating_time = ft_atoi(av[2]);
	tab->sleeping_time = ft_atoi(av[3]);
	if (count == 5)
		tab->eating_count = ft_atoi(av[4]);
}

int	main(int ac, char **av)
{
	t_table tab;

	if (ac == 5 || ac == 6)
	{
		av++;
		if (check_all(av, ac - 1) == -1)
			return (error_free("Wrong argument", &tab), 1);
		assign_arg(av, ac - 1, &tab);
		if (create_philo(&tab) == -1)
			return(1);
		return (0);
	}
	return (error_free("Invalid argument", &tab), 1);
}
