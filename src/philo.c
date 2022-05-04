#include "philo.h"

int ft_atoi(char *str)
{
	int	num;

	num = 0;

	while (*str)
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}

t_args start_args(char **argv)
{
	t_args a;
	int	j;
	int i;

	i = 1;
	j = 0;
	a.fork = malloc(sizeof(int) * ft_atoi(argv[1]));
	//x = &a.fork[0];
	while(j < ft_atoi(argv[1]))
	{
		a.fork[j] = j + 1;
		j++;
	}
	while (argv[i])
	{
		if (i == 1)
			a.phi = ft_atoi(argv[i]);
		else if (i == 2)
			a.time_to_die = ft_atoi(argv[i]);
		else if (i == 3)
			a.time_to_eat = ft_atoi(argv[i]);
		else if (i == 4 )
			a.time_to_sleep = ft_atoi(argv[i]);
		else if (i == 5)
			a.num_otepmeat = ft_atoi(argv[i]);
		i++;
	}
	return (a);
}

int main(int argc, char **argv)
{
	t_args a;

	if (argc == 5 || argc == 6)
	{
		a = start_args(argv);
		start_philos(&a);
	}
	else
		printf("Invalid No ARGS\n");
	return (0);
}
