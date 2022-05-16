/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:22:58 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/15 21:10:28 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	milli(void)
{
	int long		c_time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	c_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (c_time);
}

void	*check_live(void *philo)
{
	t_state_philo	*t;

	t = philo;
	while (1)
	{
		sem_wait(t->args->check_e);
		if ((milli() - t->is_eating) > t->args->time_to_die)
		{
			print_msg(t->args, t->id, milli() - t->is_eating, "died");
			sem_post(t->args->check_kill);
			exit (0);
		}
		sem_post(t->args->check_e);
	}
	return (NULL);
}

void	*check_k5(void *phi)
{
	t_state_philo	*p;
	int				i;

	p = phi;
	sem_wait(p->args->check_kill);
	i = 0;
	while (i < p->args->phi)
	{
		kill(p[i].proc_id, SIGTERM);
		i++;
	}
	return (NULL);
}

void	print_msg(t_args *a, int id, long current, char *s)
{
	sem_wait(a->msg);
	printf("%ld %d %s\n", current, id, s);
	sem_post(a->msg);
}

void	free_all(t_state_philo *p)
{
	free (p);
}
