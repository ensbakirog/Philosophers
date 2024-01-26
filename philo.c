#include <unistd.h>
#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if ((ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0
			|| ft_atoi(av[4]) < 0) || (ac == 6 && ft_atoi(av[5]) < 0))
				return (write(2, "Error: Wrong argument\n", 22), 1);
		return (0);
	}
	return (write(2, "Error: Invalid argument\n", 24), 1);
}
