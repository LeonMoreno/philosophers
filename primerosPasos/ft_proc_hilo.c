/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_hilo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:31:32 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/14 17:06:54 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

struct s_args;

typedef struct s_philo
{
	int	id;
	pid_t pid;
	struct s_args *args;
	pthread_t	th;
} t_philo;

typedef struct s_args
{
	int num;
	t_philo philo[10];
	sem_t *print;
	sem_t *check;
}	t_args;

void *ft_hilo(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	sem_wait(philo->args->check);
	philo->args->num = 100;
	printf("Sou el HILO %d\n", philo->id);
	sem_post(philo->args->check);
	//if (philo->args->num == 100)
	//	exit (0);
	printf("** EN PROC %d args.num = %d **\n", philo->id, philo->args->num);
		return (NULL);
}

void ft_fork(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	pthread_create(&(p->th), NULL, ft_hilo, philo);
	if (p->id % 2)
		usleep(15000);
	printf("PROC args DIR = %p\n", p->args);
	sem_wait(p->args->print);
	usleep(15000);
	sem_post(p->args->print);
	pthread_join(p->th, NULL);
	exit (0);
}

void start_sem(t_args *a)
{
	sem_unlink("/print");
	sem_unlink("/check");
	a->print = sem_open("/print", O_CREAT | O_EXCL, S_IRWXU, 1);
	a->check = sem_open("/check", O_CREAT | O_EXCL, S_IRWXU, 1);
}

int main(void)
{
	t_philo *p;
	t_args args;
	int	i;
	int status;

	i = 0;
	args.num = 7;
	start_sem(&args);
	printf("ANTES args DIR = %p\n", &args);
	printf("ANTES args.num = %d\n", args.num);
	p = args.philo;
	while (i < 3)
	{
		p[i].args = &args;
		p[i].id = i;
		p[i].pid = fork();
		if (p[i].pid == 0)
			ft_fork(&(p[i]));
		usleep(100);
		i++;
	}

	i = 0;
	while (i < 3)
	{
		waitpid(p[i].pid, &status, 0);
		i++;
	}
	printf("DESPUES args.num = %d\n", args.num);
	return (0);
}
