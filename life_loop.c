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

int is_thinking(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time == -1)
		return (-1);
	time = time - philo->table->start;
	printf("%lld %d is thinking\n", time, philo->id);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time == -1)
		return (-1);
	time = time - philo->table->start;
	printf("%lld %d is sleeping\n", time, philo->id);
	usleep(philo->table->s_time * 1000);
	return (0);
}

int	take_forks(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->table->mutex);
	time = get_time();
	if (time == -1)
		return (-1);
	philo->self_fork = false;
	time -= philo->table->start;
	printf(GREEN"%lld %d has taken a fork\n"RESET, time, philo->id);
	time = get_time();
	if (time == -1)
		return (-1);
	*(philo->other_fork) = false;
	time -= philo->table->start;
	printf(GREEN"%lld %d has taken a fork\n"RESET, time, philo->id);
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int	is_eating(t_philo *philo)
{
	long long	time;

	if (philo->self_fork ==	true  && *philo->other_fork == true)
	{
		take_forks(philo);
		time = get_time();
		if (time == -1)
			return (-1);
		printf(YELLOW"%lld %d is eating\n"RESET, time - philo->table->start, philo->id);
		usleep(philo->table->e_time * 1000);
		philo->self_fork = true;
		*philo->other_fork = true;
	}
	return (0);
}
