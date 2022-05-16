/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:59:56 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/15 21:11:44 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	ft_philo_eat(t_state_philo *p)
{
	sem_wait(p->args->forks);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a fork");
	sem_wait(p->args->forks);
	print_msg(p->args, p->id, milli() - p->born, "Has taken a fork");
	p->current = milli();
	p->is_eating = milli();
	print_msg(p->args, p->id, milli() - p->born, "is eating");
	while ((milli() - p->current) < p->args->time_to_eat)
		p->eat++;
	p->xnum_eat++;
	sem_post(p->args->forks);
	sem_post(p->args->forks);
}

void	ft_procstart(t_state_philo *p)
{
	pthread_t	th;

	p->born = milli();
	pthread_create(&th, NULL, check_live, p);
	if (p->id % 2 == 0)
		usleep(p->args->time_to_eat * 1000);
	while (!p->args->died)
	{
		ft_philo_eat(p);
		if (p->xnum_eat == p->args->nx_eat)
			exit (0);
		print_msg(p->args, p->id, milli() - p->born, "is sleeping");
		usleep(p->args->time_to_sleep * 1000);
		print_msg(p->args, p->id, milli() - p->born, "is thinking");
	}
	pthread_join(th, NULL);
	exit (0);
}

static	void	start_sem(t_args *a)
{
	sem_unlink("/forks");
	sem_unlink("/msg");
	sem_unlink("/check_e");
	sem_unlink("/check_kill");
	a->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, a->phi);
	a->check_e = sem_open("/check_e", O_CREAT | O_EXCL, S_IRWXU, 1);
	a->msg = sem_open("/msg", O_CREAT | O_EXCL, S_IRWXU, 1);
	a->check_kill = sem_open("/check_kill", O_CREAT | O_EXCL, S_IRWXU, 0);
}

static	void	end_philos(t_state_philo *p)
{
	int			i;
	int			status;
	pthread_t	id_kill;

	i = 0;
	pthread_create(&id_kill, NULL, check_k5, p);
	while (i < p->args->phi)
	{
		waitpid(p[i].proc_id, &status, 0);
		i++;
	}
	sem_close(p->args->forks);
	sem_close(p->args->check_e);
	sem_close(p->args->msg);
	sem_close(p->args->check_nx_eat);
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
			ft_procstart(&p[i]);
		i++;
	}
	end_philos(p);
	free_all(p);
}
