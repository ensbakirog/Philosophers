/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebakirog <ebakirog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:40:56 by ebakirog          #+#    #+#             */
/*   Updated: 2024/02/07 23:34:12 by ebakirog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

long long	get_time(void)
{
	long long	time;
	struct timeval	watch;

	if (gettimeofday(&watch, NULL) != 0)
		return (error_msg("Time Error"), -1);
	time = (watch.tv_sec * 1000) + (watch.tv_usec / 1000);
	return (time);
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

int	check_all(char **av, int count)
{
	if (ft_atoi(av[0]) < 1)
		return (-1);
	else if (ft_atoi(av[1]) < 0)
		return (-1);
	else if (ft_atoi(av[2]) < 0)
		return (-1);
	else if (ft_atoi(av[3]) < 0)
		return (-1);
	else if (count == 5 && ft_atoi(av[4]) < 0)
		return (-1);
	return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if ((num > 2147483648 && sign == -1) || (num > 2147483647 && sign == 1))
		return (-1);
	return (num * sign);
}

void	error_msg(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	write(2, "ERROR: ", 7);
	write(2, str, i);
	write(2, "\n", 1);
}
