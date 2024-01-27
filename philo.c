#include <unistd.h>
#include "philo.h"
#include <stdlib.h>

void	free_table(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->p_count)
	{
		if (table->philo[i] != NULL)
			free(table->philo[i]);
	}
	if (table->philo != NULL)
		free(table->philo);
}


int create_philo(t_table *table)
{
	int i;

	i = -1;
	table->philo = (t_philo **)malloc(sizeof(t_philo *) * table->p_count);
	if (table->philo == NULL)
		return (free_table(table), -1);
	while (++i < table->p_count)
	{
		table->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (table->philo[i] == NULL)
			return (free_table(table), -1);
		table->philo[i]->philo_id = i + 1;
	}
	return (0);
}

void	assign_arg(char **av, int count, t_table *table)
{
	table->p_count = ft_atoi(av[0]);
	table->death_time = ft_atoi(av[1]);
	table->eating_time = ft_atoi(av[2]);
	table->sleeping_time = ft_atoi(av[3]);
	if (count == 5)
		table->eating_count = ft_atoi(av[4]);
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

int	main(int ac, char **av)
{
	t_table table;

	if (ac == 5 || ac == 6)
	{
		av++;
		if (check_all(av, ac - 1) == -1)
			return (error_msg("Wrong argument"), 1);
		assign_arg(av, ac - 1, &table);
		if (create_philo(&table) == -1)
			return(error_msg("Malloc error"), 1);
		return (0);
	}
	return (error_msg("Invalid argument"), 1);
}
