/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:22:58 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/12 15:14:25 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	milli(void)
{
	int long		c_time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	c_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (c_time);
}

int	check_live(t_state_philo *t)
{
	int	i;

	while (t->args->died == 0)
	{
		i = 0;
		while (i < t->args->phi)
		{
			pthread_mutex_lock(&t->args->check_eat);
			if ((milli() - t[i].is_eating) > t->args->time_to_die)
			{
				t->args->died = 1;
				print_msg(t->args, t[i].id, milli() - t[i].is_eating, "died");
				return (0);
			}
			pthread_mutex_unlock(&t->args->check_eat);
			i++;
		}
	}
	return (1);
}

void	print_msg(t_args *a, int id, long current, char *s)
{
	pthread_mutex_lock(&a->msg);
	printf("%ld %d %s\n", current, id, s);
	pthread_mutex_unlock(&a->msg);
}

void	free_all(t_state_philo *p)
{
	free (p->args->mutex);
	free (p);
}
