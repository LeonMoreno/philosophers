/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:10:36 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/16 12:43:14 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_state_philo	*start_philos(t_args *args)
{
	int				i;
	t_state_philo	*p;

	i = 0;
	p = malloc(sizeof(t_state_philo) * args->phi);
	if (!p)
		return (NULL);
	while (i < args->phi)
	{
		p[i].id = i + 1;
		p->eat = 0;
		p->current = 0;
		p[i].is_eating = milli();
		p[i].args = args;
		i++;
	}
	return (p);
}

int	main(int argc, char **argv)
{
	t_args			a;
	t_state_philo	*p;

	if (argc == 5 || argc == 6)
	{
		if (!(start_args(argc, argv, &a)))
		{
			printf("Invalid ARGS\n");
			return (1);
		}
		p = start_philos(&a);
		start_mutex(&a);
		start_pthreads(p);
	}
	else
		printf("Invalid No ARGS\n");
	return (0);
}
