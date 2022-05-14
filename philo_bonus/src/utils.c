/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:22:58 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/14 17:14:13 by lmoreno          ###   ########.fr       */
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
	t_state_philo *t;

	t = (t_state_philo *)philo;
	t =  philo;
	while (1)
	{
		printf("PROC %d AQui TOY\n", t->id);
		sem_wait(t->args->check_e);	
		if ((milli() - t->is_eating) > t->args->time_to_die)
		{
			t->args->died = 1;
			print_msg(t->args, t->id, milli() - t->is_eating, "died");
			return (NULL);
		}
		sem_post(t->args->check_e);
		//usleep(1000);
		if (t->args->died == 1)
		{
			exit (0);
		}
	}

	return (NULL);
}

void	print_msg(t_args *a, int id, long current, char *s)
{
//	pthread_mutex_lock(&a->msg);
	sem_wait(a->msg);
	printf("%ld %d %s\n", current, id, s);
	sem_post(a->msg);
//	pthread_mutex_unlock(&a->msg);
}

void	free_all(t_state_philo *p)
{
	//free (p->args->mutex);
	free (p);
}
