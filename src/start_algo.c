/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:59:56 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/09 13:29:46 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	ft_philo_eat(t_state_philo *p,
	pthread_mutex_t *f_r, pthread_mutex_t *f_l)
{
	pthread_mutex_lock(f_l);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a Tenedor");
	pthread_mutex_lock(f_r);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a Tenedor");
	p->current = milli();
	p->is_eating = milli();
	print_msg(p->args, p->id, milli() - p->born, "is eating");
	while ((milli() - p->current) < p->args->time_to_eat)
		p->eat++;
	pthread_mutex_unlock(f_l);
	pthread_mutex_unlock(f_r);
}

void	*ft_pthread(void *philo)
{
	t_state_philo	*p;
	pthread_mutex_t	*f_r;
	pthread_mutex_t	*f_l;

	p = ((t_state_philo *)philo);
	p->born = milli();
	p->eat = 0;
	p->current = 0;
	if (p->id == 1)
		f_l = &p->args->mutex[p->args->phi - 1];
	else
		f_l = &p->args->mutex[p->id - 2];
	f_r = &p->args->mutex[p->id - 1];
	if (p->id % 2)
		usleep(15007);
	while (!p->args->died)
	{
		ft_philo_eat(philo, f_r, f_l);
		p->xnum_eat++;
		if (p->xnum_eat == p->args->nx_eat)
			break ;
		print_msg(philo, p->id, milli() - p->born, "is Sleeping");
		usleep(p->args->time_to_sleep * 1000);
	}
	return (NULL);
}

static	void	start_mutex(t_args *a)
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

void	start_philos(t_args *args)
{
	int				i;
	t_state_philo	*p;

	i = 0;
	p = malloc(sizeof(t_state_philo) * args->phi);
	if (!p)
		return ;
	start_mutex(args);
	while (i < args->phi)
	{
		p[i].id = i + 1;
		p[i].is_eating = milli();
		p[i].args = args;
		pthread_create(&p[i].thread_id, NULL, ft_pthread, &p[i]);
		i++;
	}
	if (args->nx_eat == 0)
	{
		if (!check_live(p))
			return ;
	}
	end_philos(p);
}
