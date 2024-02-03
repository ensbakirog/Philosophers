#include <unistd.h>
#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

long long	get_time(void)
{
	long long time;
	struct timeval watch;
	if (gettimeofday(&watch, NULL) != 0)
		return (-1);
	time = watch.tv_sec * 1000;
	return (time);
}

int	is_sleeping(t_philo *philo)
{
	long long time;
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lld %d is sleeping\n", time - philo->table->start_time, philo->philo_id);
	usleep(philo->table->sleeping_time * 1000);
	return (0);
}

void	*life_loop(void *arg)
{
	is_sleeping(arg);
	return (NULL);
}

int create_philo(t_table *tab)
{
	int i;

	i = -1;
	tab->philo = (t_philo *)malloc(sizeof(t_philo) * tab->p_count);
	if (tab->philo == NULL)
		return (error_msg("Malloc Error"), -1);
	while (++i < tab->p_count)
		tab->philo[i].table = tab;
	tab->start_time = get_time();
	if (tab->start_time == -1)
		return(error_msg("Time Error"), free(tab->philo), -1);
	i = -1;
	while (++i < tab->p_count)
	{
		tab->philo[i].philo_id = i + 1;
		if (pthread_create(&tab->philo[i].thread, NULL, &life_loop, &tab->philo[i]) != 0)
			return (error_msg("Thread Create"), free(tab->philo), -1);
	}
	i = -1;
	while (++i < tab->p_count)
	{
		if (pthread_join(tab->philo[i].thread, NULL) != 0)
			return (error_msg("Thread Join"), free(tab->philo), -1);
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
			return (error_msg("Wrong Argument"), 1);
		assign_arg(av, ac - 1, &tab);
		if (create_philo(&tab) == -1)
			return(1);
		return (0);
	}
	return (error_msg("Invalid Argument"), 1);
}
