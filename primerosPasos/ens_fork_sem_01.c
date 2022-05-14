/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ens_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:51:13 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/14 10:57:24 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct s_ens
{
	sem_t *sem_1;
}	t_ens;

void ft_child(t_ens *ens)
{
	sem_wait(ens->sem_1);
	printf("Chao\n");	
	sem_close(ens->sem_1);
	exit(0);
}

int main(void)
{
	pid_t pid;
	int	status;
	t_ens ens;

	ens.sem_1 = sem_open("/sem_1", O_CREAT | O_EXCL, S_IRWXU, 0);

	pid = fork();
	if (pid == 0)
		ft_child(&ens);
	
	
		//sleep(1);
		printf("Hola\n");
		//sem_post(ens.sem_1);	
		sem_close(ens.sem_1);
		sem_unlink("/sem_1");	
	
	waitpid(pid, &status, 0);
	return(7);

}
