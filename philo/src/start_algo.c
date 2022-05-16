/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:59:56 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/16 12:47:37 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	ft_philo_eat(t_state_philo *p)
{
	pthread_mutex_lock(p->f_l);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a fork");
	pthread_mutex_lock(p->f_r);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a fork");
	p->current = milli();
	p->is_eating = milli();
	print_msg(p->args, p->id, milli() - p->born, "is eating");
	while ((milli() - p->current) < p->args->time_to_eat)
		p->eat++;
	p->xnum_eat++;
	pthread_mutex_unlock(p->f_l);
	pthread_mutex_unlock(p->f_r);
}

void	*ft_pthread(void *philo)
{
	t_state_philo	*p;

	p = ((t_state_philo *)philo);
	p->born = milli();
	if (p->id == 1)
		p->f_l = &p->args->mutex[p->args->phi - 1];
	else
		p->f_l = &p->args->mutex[p->id - 2];
	p->f_r = &p->args->mutex[p->id - 1];
	if (p->id % 2)
		usleep(15007);
	while (!p->args->died)
	{
		ft_philo_eat(philo);
		if (p->xnum_eat == p->args->nx_eat)
		{
			p->args->brek = 1;
			break ;
		}
		print_msg(philo, p->id, milli() - p->born, "is Sleeping");
		usleep(p->args->time_to_sleep * 1000);
		print_msg(p->args, p->id, milli() - p->born, "is thinking");
	}
	return (NULL);
}

void	start_mutex(t_args *a)
{
	int	i;

	i = 0;
	a->mutex = malloc(sizeof(int) * a->phi);
	if (!a->mutex)
		return ;
	while (i < a->phi)
	{
		pthread_mutex_init(&a->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&a->msg, NULL);
	pthread_mutex_init(&a->check_eat, NULL);
}

static	void	end_philos(t_state_philo *p)
{
	int	i;

	i = 0;
	while (i < p->args->phi)
	{
		pthread_join(p[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < p->args->phi)
	{
		pthread_mutex_destroy(&p->args->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&p->args->msg);
	pthread_mutex_destroy(&p->args->check_eat);
}

void	start_pthreads(t_state_philo *p)
{
	int				i;

	i = 0;
	while (i < p->args->phi)
	{
		pthread_create(&p[i].thread_id, NULL, ft_pthread, &p[i]);
		i++;
	}
	if (!check_live(p))
		return ;
	end_philos(p);
	free_all(p);
}
