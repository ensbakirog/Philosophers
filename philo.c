#include <unistd.h>
#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

int	take_right_fork(t_philo *philo)
{
	long long time;

	time = get_time();
	if (time == -1)
		return (-1);
	philo->self_fork = in_use;
	printf("%lld %d has taken right fork\n", time - philo->table->start, philo->id);
	time = get_time();
	if (time == -1)
		return (-1);
	philo->other_fork = in_use;
	printf("%lld %d has taken left fork\n", time - philo->table->start, philo->id);
	return (0);
}

void	create_fork(t_table *tab)
{
	int i;
	int x;

	i = -1;
	while (++i < tab->p_count)
	{
		tab->philo[i].self_fork = available;
		x = ((i - 1) + tab->p_count) % tab->p_count;
		tab->philo[i].other_fork = &tab->philo[x].self_fork;
	}
}

int is_eating(t_philo *philo)
{
	long long time;
	if (philo->self_fork == 1 && philo->other_fork == 1)
	{
		take_forks(philo);
		time = get_time();
		if (time == -1)
			return (-1);
		printf("%lld %d is eating\n", time - philo->table->start, philo->id);
		usleep(philo->table->e_time * 1000);
		return (0);
	}
}

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
	printf("%lld %d is sleeping\n", time - philo->table->start, philo->id);
	usleep(philo->table->s_time * 1000);
	return (0);
}

void	*life_loop(void *arg)
{
	is_eating(arg);
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
	tab->start = get_time();
	if (tab->start == -1)
		return(error_msg("Time Error"), free(tab->philo), -1);
	i = -1;
	while (++i < tab->p_count)
	{
		tab->philo[i].id = i + 1;
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
	tab->d_time = ft_atoi(av[1]);
	tab->e_time = ft_atoi(av[2]);
	tab->s_time = ft_atoi(av[3]);
	if (count == 5)
		tab->e_count = ft_atoi(av[4]);
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
		create_fork(&tab);
		if (pthread_mutex_init(&tab.mutex, NULL) != 0)
			return (error_msg("Mutex İnit"), free(tab.philo), 1);
		if(pthread_mutex_destroy(&tab.mutex) != 0)
			return (error_msg("Mutex Destroy"), free(tab.philo), 1);
		return (0);
	}
	return (error_msg("Invalid Argument"), 1);
}
