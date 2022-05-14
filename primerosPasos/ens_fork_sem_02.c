/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ens_fork_sem_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:36:50 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/13 16:37:23 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ens_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:51:13 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/13 16:36:42 by lmoreno          ###   ########.fr       */
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
	int		ensayo;
	sem_t *fork_0;
}	t_argu;

typedef struct s_philo
{
	int id;
	int eat;
	long	last_eat;
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
	
	current = milli();
	p->eat = 0;
	printf("Soy el Hijo No %d ENSAYo = %d\n", p->id, p->argu->ensayo);	
	printf("Dir argu = %p\n", p->argu);
	p->argu->ensayo = 42;
	sem_wait(p->argu->fork_0);
	sem_wait(p->argu->fork_0);
	while ((milli() - current) < 200)
		p->eat++;
	p->last_eat = milli();
	sem_post(p->argu->fork_0);
	sem_post(p->argu->fork_0);
	printf("Soy el Hijo No %d EAT = %d\n", p->id, p->eat);	
	sem_close(p->argu->fork_0);
	exit(0); 
}

/* Aqui estoy comprobando como el espacio de memoria de cada proceso
 * es independiente, pues se crea una copia de todo para cada uno.
 * Y luego desde el main() no puedo acceder a la info de estos.
 * ULTRA IMPORTANTE HACER PRIMERO sem_unlink(...);
 */

int main(void)
{
	
	int	status;
	t_philo *philo;
	t_argu argu;
	int i;

	i = 0;
	argu.ensayo = 7;
	sem_unlink("/fork_0");
	argu.fork_0 = sem_open("/fork_0", O_CREAT | O_EXCL, S_IRWXU, 3);
	philo = malloc(sizeof(t_philo) * 3);
	printf("Dir argu = %p\n", &argu);
	while (i < 3)
	{
		philo[i].id = i;
		philo[i].argu = &argu;
		philo[i].proc = fork();
		if (philo[i].proc == 0)
			start_philo(&philo[i]);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		waitpid(philo[i].proc, &status, 0);
		i++;
	}
	printf("argu_ensauo = %d\n", argu.ensayo);
	printf("Soy el Hijo No %d EAT = %d\n", philo[0].id, philo[0].eat);	
	printf("Soy el Hijo No %d EAT = %d\n", philo[1].id, philo[1].eat);	
	printf("Soy el Hijo No %d EAT = %d\n", philo[1].id, philo[1].eat);	

	return(0);

}
