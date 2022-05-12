/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ens_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:51:13 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/11 19:34:41 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_argu
{
	int ensayo;
	sem_t *forks;
}	t_argu;

typedef struct s_philo
{
	int id;
	pid_t proc;
	t_argu *argu;
} t_philo;

long int milli(void)
{
	struct timeval tp;
	int long current;

	gettimeofday(&tp, NULL);
	current = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (current);
}


void start_philo(t_philo *p)
{
	long int current;
	int eat;
	
	current = milli();
	eat = 0;
	printf("Soy el Hijo No %d PROC = %d\n", p->id, getpid());	
	sem_wait(p->argu->forks);
	sem_wait(p->argu->forks);
	while ((milli() - current) < 200)
		eat++;
	sem_post(p->argu->forks);
	//sem_post(p->argu->forks);
	printf("Soy el Hijo No %d EAT = %d\n", p->id, eat);	
	sem_close(p->argu->forks);
}

int main(void)
{
	
	int	status;
	t_philo *philo;
	t_argu argu;
	int i;

	i = 0;
	argu.ensayo = 7;
	argu.forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, 3);
	philo = malloc(sizeof(t_philo) * 3);
	while (i < 3)
	{
		philo[i].id = i;
		philo[i].argu = &argu;
		philo[i].proc = fork();
		if (philo[i].proc == 0)
		{
			start_philo(&philo[i]);
			exit (0);
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		waitpid(philo[i].proc, &status, 0);
		i++;
	}
	return(0);

}
