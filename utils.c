#include <unistd.h>
#include "philo.h"
#include <stdlib.h>

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

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	error_free(char *str, t_table *tab)
{
	int i;

	i = -1;
	while (++i < tab->p_count)
	{
		if (tab->philo[i])
			free(tab->philo[i]);
	}
	if (tab->philo)
		free(tab->philo);
	write (2, "Error\n", 6);
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
}
