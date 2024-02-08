/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebakirog <ebakirog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:40:51 by ebakirog          #+#    #+#             */
/*   Updated: 2024/02/07 23:22:38 by ebakirog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	*life_loop(void *arg)
{
	while (1)
	{
		is_eating(arg);
		is_sleeping(arg);
	}
	return (NULL);
}

int	create_philo(t_table *tab)
{
	int	i;

	i = -1;
	tab->philo = (t_philo *)malloc(sizeof(t_philo) * tab->p_count);
	if (tab->philo == NULL)
		return (error_msg("Malloc Error"), -1);
	while (++i < tab->p_count)
		tab->philo[i].table = tab;
	tab->start = get_time();
	if (tab->start == -1)
		return (error_msg("Time Error"), free(tab->philo), -1);
	i = -1;
	while (++i < tab->p_count)
	{
		tab->philo[i].id = i + 1;
		if (pthread_create(&tab->philo[i].thread, NULL, &life_loop,
				&tab->philo[i]) != 0)
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

int	main(int ac, char **av)
{
	t_table	tab;

	if (ac == 5 || ac == 6)
	{
		av++;
		if (check_all(av, ac - 1) == -1)
			return (error_msg("Wrong Argument"), 1);
		assign_arg(av, ac - 1, &tab);
		if (create_philo(&tab) == -1)
			return (1);
		create_fork(&tab);
		if (pthread_mutex_init(&tab.mutex, NULL) != 0)
			return (error_msg("Mutex İnit"), free(tab.philo), 1);
		if (pthread_mutex_destroy(&tab.mutex) != 0)
			return (error_msg("Mutex Destroy"), free(tab.philo), 1);
		return (0);
	}
	return (error_msg("Invalid Argument"), 1);
}
