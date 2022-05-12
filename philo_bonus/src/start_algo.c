/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:59:56 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/12 18:55:09 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	ft_philo_eat(t_state_philo *p)
{
	sem_wait(p->args->forks);
	sem_wait(p->args->forks);
	//pthread_mutex_lock(p->f_l);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a fork");
	//pthread_mutex_lock(p->f_r);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a fork");
	p->current = milli();
	p->is_eating = milli();
	print_msg(p->args, p->id, milli() - p->born, "is eating");
	while ((milli() - p->current) < p->args->time_to_eat)
		p->eat++;
	p->xnum_eat++;
	//pthread_mutex_unlock(p->f_l);
	//pthread_mutex_unlock(p->f_r);
	sem_post(p->args->forks);
	sem_post(p->args->forks);
}

void	ft_procstart(t_state_philo *p)
{
	int	i;
	printf("Soy El proceso %d\n", getpid());
	p->born = milli();
	p->eat = 0;
	p->current = 0;
	//if (p->id % 2)
	//	usleep(15007);
	//while (!p->args->died)
	i = 0;
	while (i < 3)
	{
		ft_philo_eat(p);
		if (p->xnum_eat == p->args->nx_eat)
		{
			p->args->brek = 1;
			break ;
		}
		//print_msg(p->args, p->id, milli() - p->born, "is Sleeping");
		//usleep(p->args->time_to_sleep * 1000);
		i++;
	}
}

static	void	start_sem(t_args *a)
{
	a->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, a->phi);
	a->msg = sem_open("/msg", O_CREAT | O_EXCL, S_IRWXU, 0);
}

static	void	end_philos(t_state_philo *p)
{
	int	i;
	int	status;

	i = 0;
	while (i < p->args->phi)
	{
		waitpid(p[i].proc_id, &status, 0);
		i++;
	}
}

void	start_philos(t_args *args)
{
	int				i;
	t_state_philo	*p;

	i = 0;
	p = malloc(sizeof(t_state_philo) * args->phi);
	if (!p)
		return ;
	start_sem(args);
	while (i < args->phi)
	{
		p[i].id = i + 1;
		p[i].is_eating = milli();
		p[i].args = args;
		p[i].proc_id = fork();
		if (p[i].proc_id == 0)
		{
			ft_procstart(&p[i]);
			exit (0);
		}
		i++;
	}
	//if (!check_live(p))
	//	return ;
	end_philos(p);
	free_all(p);
}
