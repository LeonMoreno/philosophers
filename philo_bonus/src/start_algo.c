/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:59:56 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/14 17:14:10 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*static	void	ft_philo_eat(t_state_philo *p)
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
}*/

void *ft_ft(void *philo)
{
	t_state_philo *p;

	p = (t_state_philo *)philo;
	sem_wait(p->args->check_e);
	printf("** PROC %d -- DIED = %d **\n", p->id, p->args->died);
	p->args->died = 7;
	sem_post(p->args->check_e);
	usleep(15000);
	return (NULL);
}

void	ft_procstart(t_state_philo *p)
{
	pthread_t th;
	
	p->born = milli();
	p->eat = 0;
	p->current = 0;
	printf("PROC = %d\n", getpid());
	pthread_create(&th, NULL, check_live, p);
	if (p->id % 2 == 0)
		usleep(p->args->time_to_eat * 1000);
	//check_live(p);
	while (!p->args->died)
	{
		//ft_philo_eat(p);
		if (p->xnum_eat == p->args->nx_eat)
		{
			p->args->brek = 1;
			break ;
		}
		printf("p->args->died = %d \n", p->args->died);
		print_msg(p->args, p->id, milli() - p->born, "is Sleeping");
		usleep(p->args->time_to_sleep * 1000);
	}
	pthread_join(th, NULL);
	exit (0);
}

static	void	start_sem(t_args *a)
{
	sem_unlink("/forks");
	sem_unlink("/msg");
	sem_unlink("/check_e");
	a->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, a->phi);
	a->check_e = sem_open("/check_e", O_CREAT | O_EXCL, S_IRWXU, 1);
	a->msg = sem_open("/msg", O_CREAT | O_EXCL, S_IRWXU, 1);
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
			ft_procstart(&p[i]);
		usleep(100);
		i++;
	}
	//if (!check_live(p))
	//	return ;
	end_philos(p);
	free_all(p);
}
