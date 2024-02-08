/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebakirog <ebakirog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:18:56 by ebakirog          #+#    #+#             */
/*   Updated: 2024/02/07 23:31:54 by ebakirog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	is_sleeping(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lld %d is sleeping\n", time - philo->table->start, philo->id);
	usleep(philo->table->s_time * 1000);
	return (0);
}

int	take_forks(t_philo *philo)
{
	long long	time;
	long long	tmp_time;

	time = get_time();
	if (time == -1)
		return (-1);
	philo->self_fork = in_use;
	tmp_time = time - philo->table->start;
	printf("%lld %d has taken right fork\n", tmp_time, philo->id);
	time = get_time();
	if (time == -1)
		return (-1);
	*(philo->other_fork) = in_use;
	tmp_time = time - philo->table->start;
	printf("%lld %d has taken left fork\n", tmp_time, philo->id);
	return (0);
}

void	create_fork(t_table *tab)
{
	int	i;
	int	x;

	i = -1;
	while (++i < tab->p_count)
	{
		tab->philo[i].self_fork = available;
		x = ((i - 1) + tab->p_count) % tab->p_count;
		tab->philo[i].other_fork = &tab->philo[x].self_fork;
	}
}

int	is_eating(t_philo *philo)
{
	long long	time;

	if (philo->self_fork == 1 && *philo->other_fork == 1)
	{
		take_forks(philo);
		time = get_time();
		if (time == -1)
			return (-1);
		printf("%lld %d is eating\n", time - philo->table->start, philo->id);
		usleep(philo->table->e_time * 1000);
	}
	return (0);
}
