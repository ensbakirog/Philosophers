#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{

	}
	return (write(2, "Error: Invalid argument\n", 24), 1);
}
