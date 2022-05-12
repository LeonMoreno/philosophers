/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:10:36 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/12 16:45:25 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	int	ft_atoi(char *str)
{
	int	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		++str;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			return (-1);
		str++;
	}
	return (num);
}

static	int	start_args(int argc, char **argv, t_args *a)
{
	a->phi = ft_atoi(argv[1]);
	a->time_to_die = ft_atoi(argv[2]);
	a->time_to_eat = ft_atoi(argv[3]);
	a->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		a->nx_eat = ft_atoi(argv[5]);
	else
		a->nx_eat = 0;
	a->died = 0;
	a->brek = 0;
	if (a->phi < 1 || a->time_to_die == -1 || a->time_to_eat == -1
		|| a->time_to_sleep == -1 || a->nx_eat == -1)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_args	a;

	if (argc == 5 || argc == 6)
	{
		if (!(start_args(argc, argv, &a)))
		{
			printf("Invalid No ARGS\n");
			return (1);
		}
		start_philos(&a);
	}
	else
		printf("Invalid No ARGS\n");
	return (0);
}
