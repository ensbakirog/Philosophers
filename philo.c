#include <unistd.h>
#include "philo.h"

int check_all(char **av, int count)
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
	if (ac == 5 || ac == 6)
	{
		av++;
		if (check_all(av, ac - 1) == -1)
			return (write(2, "Error: Wrong argument\n", 22), 1);
		return (0);
	}
	return (write(2, "Error: Invalid argument\n", 24), 1);
}
